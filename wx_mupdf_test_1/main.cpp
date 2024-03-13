#include <wx/wx.h>
#include <wx/rawbmp.h>
#include <mupdf/fitz.h>

class PdfViewerFrame;

class PdfPanel : public wxPanel {
public:
    PdfPanel(PdfViewerFrame* parent);

    void RenderPdf(const wxString& filePath);

protected:
    void OnPaint(wxPaintEvent& event);

private:
    fz_context* m_ctx = nullptr;
    fz_pixmap* m_pix = nullptr;
    wxBitmap m_bitmap;
};

class PdfViewerApp : public wxApp {
public:
    virtual bool OnInit() override;
};

class PdfViewerFrame : public wxFrame {
public:
    PdfViewerFrame(const wxString& title);

    void OnOpen(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);

private:
    PdfPanel* m_pdfPanel;

    DECLARE_EVENT_TABLE()
};

enum {
    ID_Open = wxID_HIGHEST + 1
};

BEGIN_EVENT_TABLE(PdfViewerFrame, wxFrame)
    EVT_MENU(ID_Open, PdfViewerFrame::OnOpen)
    EVT_MENU(wxID_EXIT, PdfViewerFrame::OnExit)
END_EVENT_TABLE()

PdfPanel::PdfPanel(PdfViewerFrame* parent)
    : wxPanel(parent), m_ctx(fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED)) {
    fz_register_document_handlers(m_ctx);
    SetBackgroundStyle(wxBG_STYLE_PAINT); // Use this style to prevent flickering on Windows
}

void PdfPanel::RenderPdf(const wxString& filePath) {
    fz_document* doc = nullptr;
    fz_pixmap* pix = nullptr;

    fz_try(m_ctx) {
        doc = fz_open_document(m_ctx, filePath.ToStdString().c_str());
        int page_count = fz_count_pages(m_ctx, doc);
        if (page_count > 0) {
            fz_matrix ctm = fz_scale(1, 1); // No zoom, for simplicity
            pix = fz_new_pixmap_from_page_number(m_ctx, doc, 0, ctm, fz_device_rgb(m_ctx), 0);
            int width = fz_pixmap_width(m_ctx, m_pix);
            int height = fz_pixmap_height(m_ctx, m_pix);
            unsigned char* samples = fz_pixmap_samples(m_ctx, m_pix);

            m_bitmap = wxBitmap(width, height, 24);
            wxNativePixelData data(m_bitmap);
            if (data) {
                wxNativePixelData::Iterator p(data);
                for (int y = 0; y < height; ++y) {
                    unsigned char* line = samples + y * fz_pixmap_stride(m_ctx, pix);
                    wxNativePixelData::Iterator rowStart = p;
                    for (int x = 0; x < width; ++x) {
                        p.Red() = line[x * 3];
                        p.Green() = line[x * 3 + 1];
                        p.Blue() = line[x * 3 + 2];
                        ++p;
                    }
                    p = rowStart;
                    p.OffsetY(data, 1);
                }
            }
            Refresh();
        }
    }
    fz_always(m_ctx) {
        fz_drop_pixmap(m_ctx, pix);
        fz_drop_document(m_ctx, doc);
    }
    fz_catch(m_ctx) {
        wxMessageBox("Failed to load or render PDF", "Error", wxICON_ERROR);
    }
}

void PdfPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    if (m_bitmap.IsOk()) {
        dc.DrawBitmap(m_bitmap, 0, 0, false);
    }
}

bool PdfViewerApp::OnInit() {
    if (!wxApp::OnInit()) return false;

    PdfViewerFrame* frame = new PdfViewerFrame("PDF Viewer with wxWidgets and MuPDF");
    frame->Show(true);
    return true;
}

PdfViewerFrame::PdfViewerFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Open, "&Open...\tCtrl-O", "Open a PDF file");
    menuFile->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    m_pdfPanel = new PdfPanel(this);
}

void PdfViewerFrame::OnOpen(wxCommandEvent& event) {
    wxString filePath = wxFileSelector("Choose a PDF file to open", "", "", "pdf", "PDF files (*.pdf)|*.pdf");
    if (!filePath.IsEmpty()) {
        m_pdfPanel->RenderPdf(filePath);
    }
}

void PdfViewerFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

IMPLEMENT_APP(PdfViewerApp)
