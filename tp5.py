#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# Message Publicitaire

import os,sys, time
from multiprocessing import Process, Semaphore, shared_memory, Value, set_start_method
import numpy as np

set_start_method('fork')

def p_lecteur(lId, messages, info, nbL, semNbL):
    while True:
        with semNbL:
            nbL.value+=1
            if nbL.value == 1:
                info.acquire()
                msg = messages[lId].decode()
                print("lecteur ", lId,": ",msg)

        with semNbL :
            nbL.value-=1
            if nbL.value == 0:
                info.release()
        time.sleep(1)
    
def p_redacteur(messages, info, nbL, semNbL):
    while True:
        pos = input()
        if len(pos) > 0:
            print("entrez le message :\n")
            with info:
                msg = input()
                msg = msg.encode(encoding="utf-8")
                messages[int(pos)] = msg.decode(encoding="utf-8")


if __name__ == '__main__':
    MAX = 4

    shm = shared_memory.SharedMemory(create=True, size=(MAX*1024))
    messages=np.ndarray((MAX,), dtype='|S1024', buffer=shm.buf)

    print(messages)
    info = Semaphore(1)
    nbL = Value('l', 0)
    semNbL = Semaphore(1)

    l_lecteurs = []

    for i in range(0, MAX):
        lecteur = Process(target=p_lecteur, args=(i, messages, info, nbL, semNbL))
        l_lecteurs.append(lecteur)
        lecteur.start()

    p_redacteur(messages, info, nbL, semNbL)
    
    for lecteur in l_lecteurs:
        lecteur.join()

    shm.close()
    shm.unlink()
