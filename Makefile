ARCHS = arm64 arm64e
TARGET := iphone:clang:latest:11.0
# PREFIX = $(THEOS)/toolchain/Xcode.xctoolchain/usr/bin/
PREFIX = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/
SYSROOT = $(THEOS)/sdks/iPhoneOS14.4.sdk

include $(THEOS)/makefiles/common.mk

TOOL_NAME = appleid-key-dumper

appleid-key-dumper_FILES = main.m
appleid-key-dumper_CODESIGN_FLAGS = -Sentitlements.plist
appleid-key-dumper_FRAMEWORKS = Sharing
appleid-key-dumper_INSTALL_PATH = /usr/local/bin

include $(THEOS_MAKE_PATH)/tool.mk
