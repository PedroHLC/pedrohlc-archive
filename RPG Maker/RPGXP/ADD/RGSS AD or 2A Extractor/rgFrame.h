#include <wx/frame.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>

struct SubInfo
{
	unsigned long filenamesize;
	unsigned long offset;
	unsigned long filesize;
	unsigned long magickey;
	char filename[256];
};

class rgFrame : public wxFrame
{
private:
	wxButton *m_bt3;
	wxCheckBox *m_check1;
	wxTextCtrl *m_text1;
	wxTextCtrl *m_text2;
	wxGauge *m_gauge1;

	void ExtractFile(wxString infile, wxString path, bool islog);
public:
	rgFrame();

	void OnChoiceFile(wxCommandEvent& event);
	void OnChoiceDir(wxCommandEvent& event);
	void OnExtractor(wxCommandEvent& event);
};

inline void check_path(wxString filename)
{
	char buf[256];
	memset(buf, 0, 256);
	int l = filename.Len();
	for(int i = 0; i < l; i++)
	{
		buf[i] = filename[i];
		if(buf[i] == '\\')
			mkdir(buf);
	}
}
