#include "CreateProjectDialog.h"

#include "boost/filesystem.hpp"

#include "wx/filefn.h"
#include "wx/filectrl.h"
#include "wx/generic/filedlgg.h"

#include "ElementIds.h"

#include "boost/filesystem.hpp"

using namespace boost::filesystem;

#define LEVELS_DIRECTORY_NAME L"Levels"
#define GUI_DIRECTORY_NAME L"GUI"
#define SOUNDS_DIRECTORY_NAME L"Sounds"
#define MODELS_DIRECTORY_NAME L"Models"


namespace Watercolor::CreateProjectDialog {
void CreateProjectDialog::_createProject(wxCommandEvent& eventData)
{
    std::wstring projectName = _projectNameControl->GetValue().ToStdWstring();

    path projectDirectory = absolute(projectName, _selectedDirectoryPath);

    create_directory(projectDirectory);
    create_directory(absolute(LEVELS_DIRECTORY_NAME, projectDirectory));
    create_directory(absolute(GUI_DIRECTORY_NAME, projectDirectory));
    create_directory(absolute(SOUNDS_DIRECTORY_NAME, projectDirectory));
    create_directory(absolute(MODELS_DIRECTORY_NAME, projectDirectory));

    _result = projectDirectory.wstring();

    this->Close();
}

void CreateProjectDialog::_browseDirectories(wxCommandEvent& eventData)
{
    boost::shared_ptr<wxDirDialog> openFileDialog = boost::make_shared<wxDirDialog>(this);

    if (openFileDialog->ShowModal() == wxID_OK) {
        _selectedDirectoryPath = openFileDialog->GetPath();
        _projectPath->SetLabelText(path(openFileDialog->GetPath()).filename().wstring());
    }

    _createProjectButton->Enable(!_selectedDirectoryPath.empty());
}

CreateProjectDialog::CreateProjectDialog(wxWindow* parent, std::wstring& result)
    : wxDialog(parent, wxID_ANY, "Create a project", wxDefaultPosition,
        wxSize(400, 180)),
    _result(result)
{
    // Set window properies
    this->SetBackgroundColour(wxColour(0xFF, 0xFF, 0xFF));

    _sizer = new wxFlexGridSizer(3);
    this->SetSizer(_sizer);

    auto projectNameLabel = boost::make_shared<wxStaticText>(this, wxID_ANY, L"Project name");
    _sizer->Add(projectNameLabel.get(), 1, wxALL, 10);
    _otherControls.push_back(projectNameLabel);

    _projectNameControl = boost::make_shared<wxTextCtrl>(this, wxID_ANY);
    _sizer->Add(_projectNameControl.get(), 1, wxALL | wxEXPAND, 10);

    _sizer->AddStretchSpacer();


    auto projectName = boost::make_shared<wxStaticText>(this, wxID_ANY, L"Project folder location");
    _sizer->Add(projectName.get(), 1, wxALL, 10);
    _otherControls.push_back(projectName);

    _projectPath = boost::make_shared<wxStaticText>(this, wxID_ANY, L"(Not choosen yet)");
    _sizer->Add(_projectPath.get(), 1, wxALL, 10);
    _otherControls.push_back(_projectPath);

    auto browseButton = boost::make_shared<wxButton>(this, BROWSE_DIRECTORY, L"Browse");
    _sizer->Add(browseButton.get(), 1, wxALL, 10);
    _otherControls.push_back(browseButton);


    _sizer->AddStretchSpacer();
    _sizer->AddStretchSpacer();
    _createProjectButton = boost::make_shared<wxButton>(this, CREATE_PROJECT, L"Create");
    _createProjectButton->Disable();
    _sizer->Add(_createProjectButton.get(), 0, wxALL | wxALIGN_RIGHT, 10);
}

CreateProjectDialog::~CreateProjectDialog() {}

wxBEGIN_EVENT_TABLE(CreateProjectDialog, wxDialog)
    EVT_BUTTON(CREATE_PROJECT, CreateProjectDialog::_createProject)
    EVT_BUTTON(BROWSE_DIRECTORY, CreateProjectDialog::_browseDirectories)
wxEND_EVENT_TABLE()
}