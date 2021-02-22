
#include "Custom_Close_Button_Snap.h"

BEGIN_EVENT_TABLE(Custom_Close_Button_Snap,wxPanel)

    EVT_MOTION(Custom_Close_Button_Snap::mouseMoved)

    EVT_LEFT_DOWN(Custom_Close_Button_Snap::mouseDown)

    EVT_LEFT_UP(Custom_Close_Button_Snap::mouseReleased)

    EVT_RIGHT_DOWN(Custom_Close_Button_Snap::rightClick)

    EVT_LEAVE_WINDOW(Custom_Close_Button_Snap::mouseLeftWindow)

    EVT_KEY_DOWN(Custom_Close_Button_Snap::keyPressed)

    EVT_KEY_UP(Custom_Close_Button_Snap::keyReleased)

    EVT_MOUSEWHEEL(Custom_Close_Button_Snap::mouseWheelMoved)

    EVT_PAINT(Custom_Close_Button_Snap::paintEvent)

END_EVENT_TABLE()


Custom_Close_Button_Snap::Custom_Close_Button_Snap(Custom_Window_Snap * parent, wxPoint position,

  wxSize button_size) :

  wxWindow(parent, wxID_ANY,position,button_size)
{
    this->Memory_Delete_Condition = false;

    this->SetSize(button_size);

    this->SetThemeEnabled(false);

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->SetExtraStyle(wxFULL_REPAINT_ON_RESIZE);


    wxString snap_dir = wxT("");

    char * path =  getenv ("SNAP");

    size_t path_size = strlen(path);

    for(size_t i=0;i<path_size;i++){

        snap_dir.append(1,path[i]);
    }

    wxString icon_path = snap_dir + wxT("/usr/share/icons/pane_close_icon.png");

    this->page_close_icon = new

                wxBitmap(icon_path,wxBITMAP_TYPE_ANY);


    this->SetMinSize(this->page_close_icon->GetSize());

    this->text = wxT("x");

    this->Parent_Position = parent->GetPosition();

    this->Position = position;

    this->pressedDown = false;

    this->SetPosition(this->Position);
}

Custom_Close_Button_Snap::~Custom_Close_Button_Snap()
{
    if(!this->Memory_Delete_Condition)
    {
       this->Memory_Delete_Condition = true;

       delete this->page_close_icon;
    }
}

void Custom_Close_Button_Snap::paintEvent(wxPaintEvent & evt)
{
    this->Update_Window_Data();

    wxPaintDC dc(this);

    render(dc);
}

void Custom_Close_Button_Snap::paintNow()
{
    this->Update_Window_Data();

    wxClientDC dc(this);
    this->render(dc);
}

void Custom_Close_Button_Snap::Update_Window_Data(){

     wxRect Parent_Rect = this->GetParent()->GetRect();

     wxSize Parent_Size = this->GetParent()->GetSize();

     wxSize Button_Size = this->GetSize();

     wxPoint Top_Right_Corner = Parent_Rect.GetTopRight();


     wxRect rect(this->GetSize());

     int new_point_x = Top_Right_Corner.x - Button_Size.x -10 ;

     int y_extend_for_button_window = (Parent_Size.y - Button_Size.y)/2;

     int new_point_y = Top_Right_Corner.y + y_extend_for_button_window;

     this->SetPosition(wxPoint(new_point_x,new_point_y));
}

void Custom_Close_Button_Snap::render(wxDC&  dc)
{
    wxRect rect(this->GetSize());

    dc.SetBrush(wxColour(235,235,235));

    dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1, rect.GetWidth()+2,rect.GetHeight()+2);

    wxSize Bitmap_Size = this->page_close_icon->GetSize();

    wxSize Panel_Size = rect.GetSize();

    int x_extend = Panel_Size.x - Bitmap_Size.x;

    int y_extend = Panel_Size.y - Bitmap_Size.y;

    dc.DrawBitmap(*this->page_close_icon,wxPoint(2+x_extend/2,2+y_extend/2));
}

void Custom_Close_Button_Snap::mouseDown(wxMouseEvent& event)
{
    this->pressedDown = true;

    this->paintNow();
}
void Custom_Close_Button_Snap::mouseReleased(wxMouseEvent& event)
{
    event.Skip(true);

    event.ResumePropagation(5);

    this->pressedDown = false;

    this->paintNow();
}

void Custom_Close_Button_Snap::mouseLeftWindow(wxMouseEvent& event)
{
    if (this->pressedDown)
    {
        this->pressedDown = false;
        this->paintNow();
    }
}

// currently unused events
void Custom_Close_Button_Snap::mouseMoved(wxMouseEvent& event) {}
void Custom_Close_Button_Snap::mouseWheelMoved(wxMouseEvent& event) {}
void Custom_Close_Button_Snap::rightClick(wxMouseEvent& event) {}
void Custom_Close_Button_Snap::keyPressed(wxKeyEvent& event) {}
void Custom_Close_Button_Snap::keyReleased(wxKeyEvent& event) {}
