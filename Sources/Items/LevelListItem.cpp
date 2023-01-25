#include "LevelListItem.h"

#include "boost/make_shared.hpp"

namespace Watercolor::CreateProjectDialog {
LevelListItem::LevelListItem(wxWindow* parent)
    : wxPanel(parent)
{
    _sizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(_sizer);

    auto control = boost::make_shared<wxStaticText>(this, wxID_ANY, "Test");
    _controls.push_back(control);
    _sizer->Add(control.get(), 0, wxALL, 5);
}
}