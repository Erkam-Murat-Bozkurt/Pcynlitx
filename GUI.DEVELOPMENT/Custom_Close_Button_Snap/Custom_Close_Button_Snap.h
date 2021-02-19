
#ifndef CUSTOM_CLOSE_BUTTON_SNAP_H
#define CUSTOM_CLOSE_BUTTON_SNAP_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/event.h>
#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/sizer.h>
#include "Custom_Window_Snap.h"
#include "Project_Folder_Lister.h"

class Custom_Close_Button_Snap : public wxWindow
{
public:
    Custom_Close_Button_Snap(Custom_Window_Snap * parent, wxPoint position,

      wxSize button_size);

    virtual ~Custom_Close_Button_Snap();
    void Update_Window_Data();
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void Update(){};
    void render(wxDC& dc);
    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
    bool pressedDown;
    wxString text;
    wxPoint Position;
    wxPoint Parent_Position;
    wxBitmap * page_close_icon;
    wxImage page_close_image;
    bool Memory_Delete_Condition;
    DECLARE_EVENT_TABLE()
};


#endif /* CUSTOM_CLOSE_BUTTON_SNAP_H */
