import ctypes
import os
import tkinter
import json
import sys
import random


try:
    current_dir = os.path.abspath(os.path.dirname(__file__))
    current_dir = os.path.join(current_dir,"zegodl/bin")
    os.chdir(current_dir)
    print(current_dir)
    if sys.version_info[0] >= 3 and sys.version_info[1] >= 8:
        os.add_dll_directory(current_dir)

    zego = ctypes.cdll.LoadLibrary("zegowrapper.dll")

    window = tkinter.Tk()
    window.title("ZEGO for test")
    window.geometry('480x960')

    NUMBER_OF_FRAMES = 8
    relative_height = 1 / float(NUMBER_OF_FRAMES)

    for number in range(NUMBER_OF_FRAMES):
        display_frame = tkinter.Frame(window, bg='')
        relative_y = number * relative_height
        display_frame.place(relx = 0, rely = relative_y,
                anchor = tkinter.NW, relwidth = 1, relheight = relative_height)
        frame_id = display_frame.winfo_id()
        zego.addView(ctypes.c_ulonglong(frame_id), ctypes.c_ulonglong(number))

    zego.createEngine()

    #zego.enumerateRecordingDevices()
    #zego.enumerateVideoDevices()
    #a = input()
    #zego.setRecordingDevice(ctypes.c_char_p(bytes("", 'utf-8')))
    zego.setVideoDevice(ctypes.c_char_p(bytes("@device:sw:{860BB310-5D01-11D0-BD3B-00A0C911CE86}\yyanchorvcam", 'utf-8')))

    profile = json.dumps({"bitrate": "600", "fps": "15", "resolution": "640*320"})
    zego.setVideoProfile(ctypes.c_char_p(bytes(profile, 'utf-8')))

    zego.enableVideo(ctypes.c_char_p(bytes("", 'utf-8')))

    #zego.enableHardwareEncoder()
    #zego.enableHardwareDecoder()

    uid = "fan"+str(random.randint(0,1000))
    channel = json.dumps({"channelId":"test","uid":uid})
    zego.joinChannel(ctypes.c_char_p(bytes(channel, 'utf-8')))

    window.mainloop()
finally:
    zego.leaveChannel(ctypes.c_char_p(bytes("", 'utf-8')))
    zego.destroyZegoEngine()