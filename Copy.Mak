all: chk inc bin

chk:
_PRJ_FILE_=DbgOut
!message BIN="$(VERS_BIN)"
!message INC="$(VERS_INC)"
!message LIB="$(VERS_LIB)"

!if "$(VERS_BIN)"==""
!error Your BIN variable is empty
!endif
!if "$(VERS_INC)"==""
!error Your INC variable is empty
!endif
!if "$(VERS_LIB)"==""
!error Your LIB variable is empty
!endif

########################################################

bin:$(VERS_BIN)\$(_PRJ_FILE_).exe

lib:$(VERS_LIB)\$(_PRJ_FILE_).lib

inc:$(VERS_INC)\$(_PRJ_FILE_).h


$(VERS_BIN)\$(_PRJ_FILE_).Exe: $(OutDir)\$(_PRJ_FILE_).exe
    copy $** $@ > nul

$(VERS_LIB)\$(_PRJ_FILE_).Lib: $(OutDir)\$(_PRJ_FILE_).lib
    copy $** $@ > nul

$(VERS_INC)\$(_PRJ_FILE_).h: $(_PRJ_FILE_).h
    copy $** $@ > nul


