import os

env = Environment(CC='g++',CCFLAGS='-g -lpthread -std=c++0x')
Export('env')

SConscript(['common/SConscript','net/SConscript'])
