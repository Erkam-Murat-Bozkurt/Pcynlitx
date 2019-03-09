
/*

Copyright ©  2019,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef CUSTOM_DOCKART_H
#define CUSTOM_DOCKART_H

#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/dockart.h>
#include <wx/dc.h>
#include <wx/dcclient.h>

class Custom_DockArt : public wxAuiDefaultDockArt
{
public:
  Custom_DockArt(){

      this->m_gradientType = wxAUI_GRADIENT_NONE;

      this->m_borderSize = 1;

      this->m_captionSize = 23;

      this->m_buttonSize = 20;
  }

  virtual ~Custom_DockArt(){

  }

  wxAuiDefaultDockArt * Clone() {

      return new Custom_DockArt(*this);
  }
};

#endif /* CUSTOM_DOCKART_H */
