#pragma once

#include "wx/wx.h"

#include "vector"

#include "boost/shared_ptr.hpp"

namespace Watercolor::CreateProjectDialog {
class LevelListItem : public wxPanel {
public:
    LevelListItem(wxWindow* parent);

private:
    wxSizer* _sizer;

    std::vector<boost::shared_ptr<wxWindow>> _controls;
};
}