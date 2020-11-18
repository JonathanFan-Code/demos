import ctypes
import os
import tkinter
import json
import sys
import random
import numpy as np
import threading, queue



#app_id = "aab8b8f5a8cd4469a63042fcfafe7063"
app_id = "b0630af62ce84025bb358c8b62fa7a4e"
channel_name = "test"
profile = {"bitrate": "1000", "fps": "15", "resolution": "640*480"}
uid = random.randint(0,1000)

isRobot = False

disableVideo = False
disableAudio = False
disable3A = False

baselineVideo = False

enableCustomCapture = False
customVideoSrc = ".\\data\\wudao.mp4"
customAudioSrc = ".\\data\\wudao-1-32k.wav"

loopback = False
current_dir = os.path.abspath(os.path.dirname(__file__))
customVideoSrc = os.path.join(current_dir, customVideoSrc)
customAudioSrc = os.path.join(current_dir, customAudioSrc)

if isRobot == True:
    enableCustomCapture = True

if enableCustomCapture == True:
    import cv2
    import wave



def customVCapture(queue, agora):
    cap = cv2.VideoCapture(customVideoSrc)
    rate = cap.get(cv2.CAP_PROP_FPS)
    delay = (int)(1000/rate)
    frame_counter = 0
    while True:
        if queue.empty() == False:
            cmd = queue.get()
            if cmd == 'done':
                break
        
        ret, frame = cap.read()
        if ret != True:
            break

        frame_counter += 1
        if frame_counter == cap.get(cv2.CAP_PROP_FRAME_COUNT):
            frame_counter = 0 #Or whatever as long as it is the same as next line
            cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

        h = frame.shape[0]
        w = frame.shape[1]
        #cv2.imshow("test", frame)
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2YUV_I420)
        #frame = frame.astype(np.uint8)
        data_p = frame.ctypes.data_as(ctypes.c_char_p)
        agora.pushVideoFrame(data_p, w, h)
        
        if cv2.waitKey(delay):
    	    pass

def customACapture(queue, agora):
    wf = wave.open(customAudioSrc, 'rb')
    CHUNK = 1024
    
    while True:
        if queue.empty() == False:
                cmd = queue.get()
                if cmd == 'done':
                    break
        data = wf.readframes(CHUNK)
        if len(data) > 0:
            agora.pushAudioFrame(ctypes.c_char_p(data), ctypes.c_ulong(len(data)))
        else:
            wf.rewind()
      
'''
def customACapture(queue, agora):
        frequency = 16000  # Our played note will be 440 Hz
        fs = 44100  # 44100 samples per second
        seconds = 3  # Note duration of 3 seconds

        # Generate array with seconds*sample_rate steps, ranging between 0 and seconds
        t = np.linspace(0, seconds, seconds * fs, False)

        # Generate a 440 Hz sine wave
        note = np.sin(frequency * t * 2 * np.pi)

        # Ensure that highest value is in 16-bit range
        audio = note * (2**15 - 1) / np.max(np.abs(note))
        # Convert to 16-bit data
        audio = audio.astype(np.int16)
        #agora.pushAudioFrame(audio.ctypes.data_as(ctypes.c_char_p), ctypes.c_ulong(len(audio)))
        # Start playback
        import simpleaudio as sa
        play_obj = sa.play_buffer(audio, 1, 2, fs)

        # Wait for playback to finish before exiting
        play_obj.wait_done()
'''          
vCapTask = None
vQueue = None

aCapTask = None
aQueue = None


if __name__ ==  '__main__':
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
        if disableAudio == True:
            enableAudio = json.dumps({"enable": "false"})
        agora.enableAudio(ctypes.c_char_p(bytes(enableAudio, 'utf-8')))
        
        enableVideo = json.dumps({"enable": "true"})
        if disableVideo == True:
            enableVideo = json.dumps({"enable": "false"})
        agora.enableVideo(ctypes.c_char_p(bytes(enableVideo, 'utf-8')))

        if baselineVideo == True:
            #100:high， 66:baseline
            parameter = '{"che.video.h264Profile" : 66}'
            agora.setParameters(ctypes.c_char_p(bytes(parameter, 'utf-8')))

        #agora.setAudioProfile(profile, scenario)

        if isRobot == True:
            agora.logOff()
            agora.muteAllRemoteVideoStreams()
            agora.muteAllRemoteAudioStreams()
            #agora.stopPreview()
        if enableCustomCapture == True:
            agora.enableVideoCustomCap()
            wf = wave.open(customAudioSrc, 'rb')
            agora.enableAudioCustomCap(ctypes.c_int32(wf.getframerate()), ctypes.c_int32(wf.getnchannels()))
        
        #agora.enumerateRecordingDevices()
        #agora.enumerateVideoDevices()

        #agora.setRecordingDevice(ctypes.c_char_p(bytes("{0.0.1.00000000}.{5c5eacc2-a2df-47db-9e25-5e6da81b5ae8}", 'utf-8')))
        #agora.setVideoDevice(ctypes.c_char_p(bytes("YY开播", 'utf-8')))

        channelProfile = json.dumps({"channelprofile": "1"})
        agora.setChannelProfile(ctypes.c_char_p(bytes(channelProfile,'utf-8')))

        clientRole = json.dumps({"clientrole": "1"})
        agora.setClientRole(ctypes.c_char_p(bytes(clientRole,'utf-8')))

        vprofile = json.dumps(profile)
        agora.setVideoProfile(ctypes.c_char_p(bytes(vprofile, 'utf-8')))
        
        if disable3A == True:
            parameter = '{"che.audio.bypass.apm" : true}'
            agora.setParameters(ctypes.c_char_p(bytes(parameter, 'utf-8')))

        channel = json.dumps({"channelId":channel_name,"uid":str(uid)})
        agora.joinChannel(ctypes.c_char_p(bytes(channel, 'utf-8')))

        if enableCustomCapture == True:
            try:
                vQueue = queue.Queue()
                vCapTask = threading.Thread(target=customVCapture, args=(vQueue, agora))
                vCapTask.start()  

                aQueue = queue.Queue()
                aCapTask = threading.Thread(target=customACapture, args=(aQueue, agora))
                aCapTask.start()
            except Exception as e:
                print(e)
        window.mainloop()

    except Exception as e:
        print(e)
    finally:
        if vCapTask is not None:
            vQueue.put("done")
            vCapTask.join()
        if aCapTask is not None:
            aQueue.put("done")
            aCapTask.join()
        agora.leaveChannel()
        agora.destroyEngine()
