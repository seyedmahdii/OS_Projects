from multiprocessing import Process, Value, Array, Queue, Lock
from time import sleep
# from threading import Lock


def add(lock, num, value):
    lock.acquire()

    try:
        tmp = 0
        while True:
            print('add')
            num.value += value
            tmp = num.value
            sleep(1)
            if tmp != num.value:
                print("Process conflict")
    finally:
        lock.release()


def sub(lock, num, value):
    lock.acquire()

    try:
        tmp = 0
        while True:
            print('sub')
            num.value -= value
            tmp = num.value
            sleep(1.5)
            if tmp != num.value:
                print("Process conflict")
    finally:
        lock.release()


def mul(lock, num, value):
    lock.acquire()

    try:
        tmp = 0
        while True:
            print('mul')
            num.value *= value
            tmp = num.value
            sleep(2)
            if tmp != num.value:
                print("Process conflict")
    finally:
        lock.release()


def div(lock, num, value):
    lock.acquire()

    try:
        tmp = 0
        while True:
            print('div')
            num.value /= value
            tmp = num.value
            sleep(3)
            if tmp != num.value:
                print("Process conflict")
    finally:
        lock.release()


def Show(num):
    while True:
        sleep(0.5)
        print(num.value)



if __name__ == '__main__':
    lock = Lock()

    num = Value('d', 0.0)
    arr = Array('i', range(2))
    q = Queue()
    p1 = Process(target=add, args=(lock, num, 10))
    p2 = Process(target=sub, args=(lock, num, 5))
    p3 = Process(target=mul, args=(lock, num, 2))
    p4 = Process(target=div, args=(lock, num, 4))

    show = Process(target=Show, args=(num,))
    show.start()
    sleep(1)
    p1.start()
    p2.start()
    p3.start()
    p4.start()


# https://docs.python.org/3/library/multiprocessing.html
# https://superfastpython.com/thread-mutex-lock/