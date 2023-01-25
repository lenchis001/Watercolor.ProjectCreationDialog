#pragma once

#include "string"
#include "vector"

#include "wx/filepicker.h"
#include <wx/wx.h>

#include "boost/smart_ptr.hpp"

namespace Watercolor::CreateProjectDialog {
class CreateProjectDialog : public wxDialog {
public:
    CreateProjectDialog(
        wxWindow* parent, std::wstring& result);
    ~CreateProjectDialog();

private:
    std::vector<boost::shared_ptr<wxWindow>> _otherControls;
    boost::shared_ptr<wxTextCtrl> _projectNameControl;
    boost::shared_ptr<wxStaticText> _projectPath;
    boost::shared_ptr<wxButton> _createProjectButton;
    wxSizer* _sizer;
    std::wstring _selectedDirectoryPath;
    std::wstring& _result;

    void _createProject(wxCommandEvent& eventData);
    void _browseDirectories(wxCommandEvent& eventData);

    wxDECLARE_EVENT_TABLE();
};
}