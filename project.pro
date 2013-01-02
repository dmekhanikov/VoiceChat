# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = VoiceChat
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui network
SOURCES += soundio/speex_encoder.cpp soundio/output_device.cpp main.cpp VoiceChatForm.cpp soundio/alsa_format_conversion.cpp ChatClient.cpp soundio/asoundpp.cpp soundio/format.cpp AudioHelper.cpp soundio/input_device.cpp soundio/speex_decoder.cpp
HEADERS += ChatClient.h VoiceChatForm.h soundio/speex_decoder.hpp soundio/speex_profile.hpp AudioHelper.h soundio/input_device.hpp soundio/alsa_format_conversion.hpp soundio/speex_encoder.hpp soundio/format.hpp soundio/asoundpp.hpp soundio/output_device.hpp
FORMS += VoiceChatForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -lspeex -lasound  
