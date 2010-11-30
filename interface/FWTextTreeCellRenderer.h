#ifndef Fireworks_TableWidget_FWTextTreeCellRenderer_h
#define Fireworks_TableWidget_FWTextTreeCellRenderer_h

#include "Fireworks/TableWidget/interface/FWTextTableCellRenderer.h"
#include "Fireworks/TableWidget/interface/GlobalContexts.h"

#include "TGTextEntry.h"

class FWTextTreeCellRenderer : public FWTextTableCellRenderer
{
public:
   FWTextTreeCellRenderer(const TGGC* iContext = &(getDefaultGC()),
                          const TGGC* iHighlightContext = &(getHighlightGC()),
                          Justify iJustify = kJustifyLeft)
      : FWTextTableCellRenderer(iContext, iHighlightContext, iJustify),
        m_indentation(0),
        m_editor(0),
        m_showEditor(false)
      {}

   virtual void setIndentation(int indentation = 0) { m_indentation = indentation; }
   virtual void setCellEditor(TGTextEntry *editor) { m_editor = editor; }
   virtual void showEditor(bool value) { m_showEditor = value; }
   virtual UInt_t width() const { return FWTextTableCellRenderer::width() + 15 + m_indentation; }
   virtual void draw(Drawable_t iID, int iX, int iY, unsigned int iWidth, unsigned int iHeight)
      {
         if (m_showEditor && m_editor)
         {
            m_editor->MoveResize(iX-3, iY-3, iWidth + 6 , iHeight + 6);
            m_editor->MapWindow();
            m_editor->SetText(data().c_str());
            return;
         }

         if (selected())
         {
            GContext_t c = highlightContext()->GetGC();
            gVirtualX->FillRectangle(iID, c, iX, iY, iWidth, iHeight);
            
            gVirtualX->DrawLine(iID,graphicsContext()->GetGC(),iX-1,iY-1,iX-1,iY+iHeight);
            gVirtualX->DrawLine(iID,graphicsContext()->GetGC(),iX+iWidth,iY-1,iX+iWidth,iY+iHeight);
            gVirtualX->DrawLine(iID,graphicsContext()->GetGC(),iX-1,iY-1,iX+iWidth,iY-1);
            gVirtualX->DrawLine(iID,graphicsContext()->GetGC(),iX-1,iY+iHeight,iX+iWidth,iY+iHeight);
         }
         FontMetrics_t metrics;
         font()->GetFontMetrics(&metrics);
         gVirtualX->DrawString(iID, graphicsContext()->GetGC(),
                               iX+m_indentation, iY+metrics.fAscent, 
                               data().c_str(),data().size());
      }
private:
   int            m_indentation;
   TGTextEntry    *m_editor;
   bool           m_showEditor;
};

#endif
