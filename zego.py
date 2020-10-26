import ctypes
import os
import tkinter
import json
import sys
import random
import time


channelName = "test"
profile = {"bitrate": "600", "fps": "15", "resolution": "640*320"}

isRobot = False
disableVideo = False

#disableAudio does not work for zego
disableAudio = False

disable3A = False

enableCustomCapture = False
customVideoSrc = "C:\\Users\\FJS\\Videos\\wudao.mp4"

enableHwenc = False
enableHwdec = False

if isRobot == True:
    enableCustomCapture = True

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
    #zego.setVideoDevice(ctypes.c_char_p(bytes("@device:sw:{860BB310-5D01-11D0-BD3B-00A0C911CE86}\yyanchorvcam", 'utf-8')))

    #开始视频自采集
    if enableCustomCapture == True:
        zego.enableCustomVideoCapture()
        zego.enableCustomAudioIO()
    

    vprofile = json.dumps(profile)
    zego.setVideoProfile(ctypes.c_char_p(bytes(vprofile, 'utf-8')))

    if disableVideo == False:
        zego.enableVideo(ctypes.c_char_p(bytes("", 'utf-8')))

    if enableHwenc == True:
        zego.enableHardwareEncoder()
    if enableHwdec == True:
        zego.enableHardwareDecoder()

    if disable3A == True:
        zego.disableAEC()
        zego.disableANS()
        zego.disableeAGC()

    uid = "fan"+str(random.randint(0,1000))
    channel = json.dumps({"channelId":channelName,"uid":uid})
    zego.joinChannel(ctypes.c_char_p(bytes(channel, 'utf-8')))

    if disableVideo == True:
        zego.disableVideo()

    #if disableAudio == True:
     #   zego.disableAudio()


    if enableCustomCapture == True:
        zego.startCapMedia(ctypes.c_char_p(bytes(customVideoSrc, 'utf-8')))

    if isRobot == True:
        zego.stopPreview()
        zego.stopPlayingStream()
        zego.muteSpeaker()
        zego.muteMicrophone()

    window.mainloop()
finally:
    zego.leaveChannel(ctypes.c_char_p(bytes("", 'utf-8')))
    zego.destroyZegoEngine()