#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#v1:
#tableau partagé :
    #processing array
    #shared memory
#envoie de signal pour stopper les rouleaux successivement puis s'arrete
#affiche que quand un un rouleau est stoppé

#v2:
#on affiche les rouleaux a intervalles reguliers

# Message Publicitaire

import os,sys, time
from multiprocessing import Process, Semaphore, shared_memory, Value, set_start_method
import numpy as np
import signal

set_start_method('fork')

def p_rouleau(lId, messages, info, nbL, semNbL):
    value = 0
    while True:
        with semNbL:
            nbL.value+=1
            if nbL.value == 1:
                info.acquire()
                messages[lId] = value

        with semNbL :
            nbL.value-=1
            if nbL.value == 0:
                info.release()
        time.sleep(lId/10+0.1)
        value = value+1
        if value>9:
            value = 0
    
def p_afficheur(messages, info, nbL, semNbL):
    while True:
        affichage = ""
        for i in range (0, MAX):
            affichage += messages[i].decode()
        print(affichage)
        time.sleep(0.1)

def p_stoppeur(messages, info, nbL, semNbL, rouleaux):
    stop = 0
    while stop<len(rouleaux):
        pos = input()
        with info:
            os.kill(rouleaux[stop].pid, signal.SIGUSR1)
            stop = stop +1

if __name__ == '__main__':
    MAX = 4

    shm = shared_memory.SharedMemory(create=True, size=(MAX*1024))
    messages=np.ndarray((MAX,), dtype='|S1024', buffer=shm.buf)

    print(messages)
    info = Semaphore(1)
    nbL = Value('l', 0)
    semNbL = Semaphore(1)

    l_rouleaux = []

    for i in range(0, MAX):
        rouleau = Process(target=p_rouleau, args=(i, messages, info, nbL, semNbL))
        l_rouleaux.append(rouleau)
        rouleau.start()

    afficheur = Process(target=p_afficheur, args=(messages, info, nbL, semNbL))
    afficheur.start()

    p_stoppeur(messages, info, nbL, semNbL, l_rouleaux)    
    
    for rouleau in l_rouleaux:
        rouleau.join()

    shm.close()
    shm.unlink()