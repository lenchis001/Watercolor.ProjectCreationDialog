#include "Plugin.h"

#include "CreateProjectDialog.h"

using namespace Watercolor::CreateProjectDialog;

std::wstring Plugin::getName()
{
    return L"Create project";
}

PluginType Plugin::getType()
{
    return PluginType::WELCOME_WINDOW;
}

void Plugin::onTopMenuItemClicked(const std::wstring& openedProjectPath, HWND parent) {}

std::wstring Plugin::onWelcomeWindowButtonClicked(HWND parent) {
    std::wstring result = L"";

    // That's okay, don't worry. wxWidgets library
    // will clean the memory on it's own
    new wxApp();

    wxEntryStart(NULL);

    wxWindow parentWindow;
    parentWindow.SetHWND((WXHWND)parent);
    parentWindow.AdoptAttributesFromHWND();
    wxTopLevelWindows.Append(&parentWindow);

    // This too
    CreateProjectDialog* dialog = new CreateProjectDialog(&parentWindow, result);
    dialog->ShowModal();

    wxTopLevelWindows.DeleteObject(&parentWindow);
    parentWindow.SetHWND((WXHWND)NULL);

    wxEntryCleanup();

    return result;
}

Plugin::~Plugin()
{

}