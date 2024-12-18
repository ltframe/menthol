// MIup.cpp : 定义 DLL 应用程序的导出函数。
//
#include "header.h"
#include "System.h"
#include "Attributes.h"
#include "Callbacks.h"
#include "ControlsContainers.h"
#include "ControlsStandard.h"
#include "Dialogs.h"
#include "Layout.h"
#include "Menus.h"
#include "Keyboard.h"
#include "String.h"
#include "Images.h"
#include "Handle.h"
#pragma comment(lib,"iup.lib")
#pragma comment(lib,"iup_scintilla.lib")
#pragma comment(lib,"im.lib")
#pragma comment(lib,"iupim.lib")
extern vector<callbackstruct> *_tvalues;

UserFunctionAtter iuplist[] = 
{
	{"Init",System::Init,0},
	{"Close",System::Close,0},
	{ "Clipboard", System::Clipboard, 0 },
	{ "Version", System::Version, 0 },
	{ "Timer", System::Timer, 0 },
	{ "User", System::User, 0 },
	{ "Config", System::Config, 0 },
	{ "Destroy", System::Destroy, 1 },
	{"SetAttribute",Attributes::SetAttribute,3},
	{"SetAttributes",Attributes::SetAttributes,2},
	{"ResetAttribute",Attributes::ResetAttribute,2},
	{"SetAttributeHandle",Attributes::SetAttributeHandle,3},
	{"GetAttribute",Attributes::GetAttribute,2},
	{"GetAttributeData",Attributes::GetAttributeData,2},
	{"GetAllAttributes",Attributes::GetAllAttributes,0},
	{"GetAttributes",Attributes::GetAttributes,1},
	{"CopyAttributes",Attributes::CopyAttributes,2},
	{"GetAttributeHandle",Attributes::GetAttributeHandle,2},
	{"SetGlobal",Attributes::SetGlobal,2},
	{"GetGlobal",Attributes::GetGlobal,1},
	{"MainLoop",Callbacks::MainLoop,0},
	{"MainLoopLevel",Callbacks::MainLoopLevel,0},
	{"LoopStep",Callbacks::LoopStep,0},
	{"ExitLoop",Callbacks::ExitLoop,0},
	{"Flush",Callbacks::Flush,0},
	{"SetCallback",Callbacks::SetCallback,3},
	{"Dialog",Dialogs::Dialog,1},
	{"Popup",Dialogs::Popup,3},
	{"Show",Dialogs::Show,1},
	{"ShowXY",Dialogs::ShowXY,3},
	{"Hide",Dialogs::Hide,1},
	{"FileDlg",Dialogs::FileDlg,0},
	{"MessageDlg",Dialogs::MessageDlg,0},
	{"ColorDlg",Dialogs::ColorDlg,0},
	{"FontDlg",Dialogs::FontDlg,0},
	{"ProgressDlg",Dialogs::ProgressDlg,0},
	{"ScintillaDlg",Dialogs::ScintillaDlg,0},
	{"Alarm",Dialogs::Alarm,5},
	{"GetFile",Dialogs::GetFile,1},
	{"GetColor",Dialogs::GetColor,5},
	{"GetText",Dialogs::GetText,3},
	{"ListDialog",Dialogs::ListDialog,0},
	{"Message",Dialogs::Message,2},
	{"MessageError",Dialogs::MessageError,1},
	{"MessageAlarm",Dialogs::MessageAlarm,3},
	{"LayoutDialog",Dialogs::LayoutDialog,1},
	{"ElementPropertiesDialog",Dialogs::ElementPropertiesDialog,1},
	{"Append",Layout::Append,2},
	{"Detach",Layout::Detach,1},
	{"Insert",Layout::Insert,3},
	{"Reparent",Layout::Reparent,3},
	{"GetParent",Layout::GetParent,1},
	{"GetChild",Layout::GetChild,2},
	{"GetChildPos",Layout::GetChildPos,2},
	{"GetChildCount",Layout::GetChildCount,1},
	{"GetNextChild",Layout::GetNextChild,2},
	{"GetBrother",Layout::GetBrother,1},
	{"GetDialog",Layout::GetDialog,1},
	{"GetDialogChild",Layout::GetDialogChild,2},
	{"Refresh",Layout::Refresh,1},
	{"RefreshChildren",Layout::RefreshChildren,1},
	{"Fill",ControlsContainers::Fill,0},
	{"Space",ControlsContainers::Space,0},
	{"Cbox",ControlsContainers::Cbox,1},
	{"GridBox",ControlsContainers::GridBox,1},
	{"MultiBox",ControlsContainers::MultiBox,1},
	{"Hbox",ControlsContainers::Hbox,1},
	{"Vbox",ControlsContainers::Vbox,1},
	{"Zbox",ControlsContainers::Zbox,1},
	{"Radio",ControlsContainers::Radio,1},
	{"Normalizer",ControlsContainers::Normalizer,0},
	{"Frame",ControlsContainers::Frame,1},
	{"FlatFrame",ControlsContainers::FlatFrame,1},
	{"Tabs",ControlsContainers::Tabs,1},
	{"FlatTabs",ControlsContainers::FlatTabs,1},
	{"BackgroundBox",ControlsContainers::BackgroundBox,0},
	{"ScrollBox",ControlsContainers::ScrollBox,1},
	{"FlatScrollBox",ControlsContainers::FlatScrollBox,1},
	{"DetachBox",ControlsContainers::DetachBox,1},
	{"Expander",ControlsContainers::Expander,1},
	{"Sbox",ControlsContainers::Sbox,0},
	{"Split",ControlsContainers::Split,2},
	{"AnimatedLabel",ControlsStandard::AnimatedLabel,1},
	{"Button",ControlsStandard::Button,1},
	{"FlatButton",ControlsStandard::FlatButton,1},
	{"DropButton",ControlsStandard::DropButton,1},
	{"Calendar",ControlsStandard::Calendar,0},
	{"Canvas",ControlsStandard::Canvas,1},
	{"Colorbar",ControlsStandard::Colorbar,0},
	{"ColorBrowser",ControlsStandard::ColorBrowser,0},
	{"DatePick",ControlsStandard::DatePick,0},
	{"Dial",ControlsStandard::Dial,1},
	{"Gauge",ControlsStandard::Gauge,0},
	{"Label",ControlsStandard::Label,1},
	{"FlatLabel",ControlsStandard::FlatLabel,1},
	{"FlatSeparator",ControlsStandard::FlatSeparator,0},
	{"Link",ControlsStandard::Link,2},
	{"List",ControlsStandard::List,0},
	{"ProgressBar",ControlsStandard::ProgressBar,0},
	{"Spin",ControlsStandard::Spin,0},
	{"Text",ControlsStandard::Text,0},
	{"MultiLine",ControlsStandard::MultiLine,0},
	{"Toggle",ControlsStandard::Toggle,1},
	{"FlatToggle",ControlsStandard::FlatToggle,1},
	{"Tree",ControlsStandard::Tree,0},
	{"Spinbox",ControlsStandard::Spinbox,0},
	{ "Item", Menus::Item, 2 },
	{ "Item2", Menus::Item2, 1 },
	{ "Menu", Menus::Menu, 0 },
	{ "Separator", Menus::Separator, 0 },
	{ "Submenu", Menus::Submenu, 2 },
	{ "NextField", Keyboard::NextField, 1 },
	{ "PreviousField", Keyboard::PreviousField, 1 },
	{ "GetFocus", Keyboard::GetFocus, 0 },
	{ "SetFocus", Keyboard::SetFocus, 1 },
	{ "GetKeyCodeString", Keyboard::GetKeyCodeString, 1 },
	{ "SetLanguage", String::SetLanguage, 1 },
	{ "GetLanguage", String::GetLanguage, 0 },
	{ "SetLanguageString", String::SetLanguageString, 2 },
	{ "GetLanguageString", String::GetLanguageString, 1 },
	{ "Image",Images::Image,3},
	{ "LoadImage", Images::LoadImage, 1 },
	{ "SaveImage", Images::SaveImage, 3 },
	{ "LoadAnimation", Images::LoadAnimation, 1 },
	{ "LoadAnimationFrames", Images::LoadAnimationFrames, 1 },
	{ "GetNativeHandleImage", Images::GetNativeHandleImage, 1 },
	{ "GetImageNativeHandle", Images::GetImageNativeHandle, 1 },
	{ "ImageFromImImage", Images::ImageFromImImage, 1 },
	{ "ImageToImImage", Images::ImageToImImage, 1 },
	{ "SaveImageAsText", Images::SaveImageAsText, 4 },
	{ "SetHandle",Handle::SetHandle,2},
	{ "GetHandle",Handle::GetHandle,1},
	{ "GetName",Handle::GetName,1},
	{ "GetAllNames",Handle::GetAllNames,1},
	{ "GetAllDialogs",Handle::GetAllDialogs,1},
	{ "Val", ControlsStandard::Val, 1 },
	{NULL,NULL,0}
};

MentholModuleMethod void MP_Init(VmState* vmstate)
{
	RunTimeState* iuplistptr = CreateModuleRunTime("CIup",vmstate);
	RegisterModuleFunciton(iuplistptr,iuplist);

}

