
include_directories (.)
include_directories(include ${SDL_INCLUDE_DIR})
include_directories(include ${SDL_TTF_INCLUDE_DIR})
include_directories(include ${SDL_IMAGE_INCLUDE_DIR})

add_definitions(`sdl-config --cflags`)

link_libraries(${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY})

add_library(gameui 
  uicombobox.cpp uidropdownlist.cpp uiedit.cpp uiframe.cpp
  uigui.cpp uihscrollbar.cpp uiimageborder.cpp uikeycursor.cpp
  uilabel.cpp uilineborder.cpp uipopup.cpp uipushbutton.cpp 
  uirect.cpp uiscrollframe.cpp uisdlcontrol.cpp uisdlfont.cpp
  uisdlimageobject.cpp uisdlkeyboard.cpp uisdlmouse.cpp 
  uitheme.cpp uitileview.cpp uitimer.cpp uivscrollbar.cpp 
  uiwindow.cpp uiwindowframe.cpp uiinifile.cpp uiborder.cpp 
  uiutils.cpp uiknob.cpp uiimageobject.cpp 
  uisdltimercontrol.cpp uiwidget.cpp uimouse.cpp uikey.cpp 
  uifont.cpp uidragobject.cpp uitooltip.cpp uitabview.cpp 
  gameui.h sigslot.h uiborder.h uiclipboard.h uicolor.h
  uicombobox.h uidropdownlist.h uiedit.h uifont.h uiframe.h
  uigui.h uihscrollbar.h uiimageborder.h uiimageobject.h
  uikey.h uikeyboard.h uikeycursor.h uilabel.h uilibcontrol.h 
  uilineborder.h uilist.h uimouse.h uipopup.h uipushbutton.h
  uirect.h uiscrollframe.h uisdlcontrol.h uisdlfont.h 
  uisdlimageobject.h uisdlkeyboard.h uisdlmouse.h uitheme.h
  uitileview.h uitimer.h uivscrollbar.h uiwindow.h 
  uiwindowframe.h uiinifile.h uiutils.h uiknob.h
  uisdltimercontrol.h uiwidget.h uidragobject.h uitooltip.h
  uitabview.h uispriteview.cpp uispriteview.h
)

