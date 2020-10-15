import ctypes
import os
import tkinter
import json
import sys
import random

app_id = "aab8b8f5a8cd4469a63042fcfafe7063"
#app_id = "b0630af62ce84025bb358c8b62fa7a4e"
channel_name = "fantest123"
uid = random.randint(0,1000)

try:
    current_dir = os.path.abspath(os.path.dirname(__file__))
    current_dir = os.path.join(current_dir,"agoradl/bin")
    os.chdir(current_dir)
    print(current_dir)
    if sys.version_info[0] >= 3 and sys.version_info[1] >= 8:
        os.add_dll_directory(current_dir)

    agora = ctypes.cdll.LoadLibrary("agorawrapper.dll")

    window = tkinter.Tk()
    window.title("agora for test")
    window.geometry('480x960')

    NUMBER_OF_FRAMES = 8
    relative_height = 1 / float(NUMBER_OF_FRAMES)

    for number in range(NUMBER_OF_FRAMES):
        display_frame = tkinter.Frame(window, bg='')
        relative_y = number * relative_height
        display_frame.place(relx = 0, rely = relative_y,
                anchor = tkinter.NW, relwidth = 1, relheight = relative_height)
        frame_id = display_frame.winfo_id()
        agora.addView(ctypes.c_ulonglong(frame_id))

    agora.createEngine(ctypes.c_char_p(bytes(app_id, 'utf-8')))
  
    enableAudio = json.dumps({"enable": "true"})
    agora.enableAudio(ctypes.c_char_p(bytes(enableAudio, 'utf-8')))
    
    enableVideo = json.dumps({"enable": "true"})
    agora.enableVideo(ctypes.c_char_p(bytes(enableVideo, 'utf-8')))

    
    #agora.enumerateRecordingDevices()
    #agora.enumerateVideoDevices()

    #agora.setRecordingDevice(ctypes.c_char_p(bytes("", 'utf-8')))
    #agora.setVideoDevice(ctypes.c_char_p(bytes("YY开播", 'utf-8')))

    #a = input()

    channelProfile = json.dumps({"channelprofile": "1"})
    agora.setChannelProfile(ctypes.c_char_p(bytes(channelProfile,'utf-8')))

    clientRole = json.dumps({"clientrole": "1"})
    agora.setClientRole(ctypes.c_char_p(bytes(clientRole,'utf-8')))

    profile = json.dumps({"bitrate": "600", "fps": "15", "resolution": "640*320"})
    agora.setVideoProfile(ctypes.c_char_p(bytes(profile, 'utf-8')))

    channel = json.dumps({"channelId":channel_name,"uid":str(uid)})
    agora.joinChannel(ctypes.c_char_p(bytes(channel, 'utf-8')))

    window.mainloop()

finally:
    agora.leaveChannel()
    agora.destroyEngine()