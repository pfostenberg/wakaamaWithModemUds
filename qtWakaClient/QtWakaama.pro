QT       += core gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console


# tcpdump -i lo -n udp port 5683 -X

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DEFINES += LWM2M_BOOTSTRAP

DEFINES += LWM2M_CLIENT_MODE
DEFINES += LWM2M_COAP_DEFAULT_BLOCK_SIZE=1024
DEFINES += LWM2M_LITTLE_ENDIAN
DEFINES += LWM2M_SUPPORT_SENML_JSON
DEFINES += SHA2_USE_INTTYPES_H
DEFINES += WITH_SHA256
DEFINES += WITH_TINYDTLS

# needed to read data from leshan
DEFINES += LWM2M_SUPPORT_JSON

# tests..
#DEFINES += LWM2M_SUPPORT_TLV

#DEFINES += LWM2M_FIRMWARE_UPGRADES
#DEFINES += LWM2M_DEVICE_INFO_WITH_TIME

# Qt Windows needed
DEFINES += CRT_SECURE_NO_WARNINGS

# no debugging next 2 off
DEFINES += LWM2M_WITH_LOGS
DEFINES += HAVE_VPRINTF


#DEFINES += NDEBUG
#DEFINES += DTLS_ECC
#DEFINES += DTLS_PSK

#DEFINES += WITH_LWIP
#DEFINES += IS_WINDOWS
#DEFINES += DTLS_PEERS_NOHASH
# uncomment for DTLS
DEFINES += MU_DTLS

#// Client mode, posix, with json and dtls
#DEFINES += LWM2M_CLIENT_MODE LWM2M_SUPPORT_JSON LWM2M_WITH_DTLS LWM2M_WITH_LOGS LWM2M_FIRMWARE_UPGRADES LWM2M_DEVICE_INFO_WITH_TIME
#// Enable logs
#// Enable additional features

#    ..\data\senml_common.c \

SOURCES += \
    qmain.cpp \
    mainwindow.cpp \
    ..\examples\client\lwm2mclient.c \
    ..\examples\shared\platform.c \
    ..\examples\shared\commandline.c \
    ..\core\bootstrap.c \
    ..\core\discover.c \
    ..\core\liblwm2m.c \
    ..\core\list.c \
    ..\core\management.c \
    ..\core\objects.c \
    ..\core\observe.c \
    ..\core\packet.c \
    ..\core\registration.c \
    ..\core\uri.c \
    ..\core\utils.c \
    ..\data\data.c \
    ..\data\tlv.c \
    ..\data\senml_json.c \
    ..\data\json.c \
    ..\data\json_common.c \
    ..\examples\client\object_device.c \
    ..\examples\client\object_firmware.c \
    ..\examples\client\object_location.c \
    ..\examples\client\object_test.c \
    ..\examples\client\object_server.c \
    ..\examples\client\object_connectivity_moni.c \
    ..\examples\client\object_connectivity_stat.c \
    ..\examples\client\object_access_control.c \
    ..\examples\client\system_api.c \
    ..\examples\client\object_security.c \
    ..\coap\transaction.c \
    ..\coap\block.c \
    ..\coap\er-coap-13\er-coap-13.c \
    ..\examples\shared\dtlsconnection.c \
    qtipv4ud.cpp \
    qtsimpleudp.cpp \
    tinydtls\ccm.c \
    tinydtls\crypto.c \
    tinydtls\dtls.c \
    tinydtls\dtls_prng.c \
    tinydtls\dtls_time.c \
    tinydtls\dtls_debug.c \
    tinydtls\hmac.c \
    tinydtls\netq.c \
    tinydtls\peer.c \
    tinydtls\session.c \
    tinydtls\aes\rijndael_wrap.c \
    tinydtls\sha2\sha2.c \
    tinydtls\ecc\ecc.c \
    tinydtls\aes\rijndael.c \
    modem_sim_udp.c \
    fake_time.c


HEADERS += \
    mainwindow.h \
    win_fake_include\unistd.h \
    dtls_config.h \
    qtipv4ud.h \
    qtsimpleudp.h \
    include\liblwm2m.h


INCLUDEPATH  += C:\Users\mza\Downloads\wakaama-master\include
INCLUDEPATH  += C:\Users\mza\Downloads\wakaama-master\examples\shared
INCLUDEPATH  += C:\Users\mza\Downloads\wakaama-master\core
INCLUDEPATH  += C:\Users\mza\Downloads\wakaama-master\qtWakaClient\win_fake_include
INCLUDEPATH  += ..\coap
INCLUDEPATH  +=  tinydtls


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
