import os

def baz():
    print("open the file..")
    foo = open("does not exist")


def bar():
    print("bar")
    baz()
    raise Exception


def foo():
    try:
        print("hi")
        bar()
        print("you won't see this")
    except:
        print("exception")

foo()
