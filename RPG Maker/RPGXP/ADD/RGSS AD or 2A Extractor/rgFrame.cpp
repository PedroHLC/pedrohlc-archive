#include "rgFrame.h"

// wx lib
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/colour.h>
#include <wx/hyperlink.h>
#include <wx/checkbox.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/wfstream.h>
#include <wx/icon.h>

// standard lib
#include <iostream>
#include <vector>
#include <windows.h>
#include <commctrl.h>


using namespace std;

// hyperlink need this lib
#ifdef _DEBUG
	#pragma comment(lib, "wxmsw28d_adv.lib")
#else
	#pragma comment(lib, "wxmsw28_adv.lib")
#endif

enum
{
	ID_BUTTON1 = 100,
	ID_BUTTON2,
	ID_BUTTON3,
	ID_LINK1
};

rgFrame::rgFrame()
  : wxFrame(NULL, wxID_ANY,
			wxT("RGSSAD 解包器 (revision 080814)"),
			wxDefaultPosition,	// 显示在默认的坐标
			wxSize(430, 180),
			wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX),
			wxT("mainframe"))
{
	// call InitCommonControls for manifest
	INITCOMMONCONTROLSEX InitControlS;
	InitControlS.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitControlS.dwICC = ICC_PROGRESS_CLASS | ICC_COOL_CLASSES;
	InitCommonControlsEx(&InitControlS);
	// SetIcon
	SetIcon(wxIcon(wxT("IDI_ICON1")));
	// create a panel contain all the controls
	wxPanel *panel = new wxPanel(this, wxID_ANY);
	// create labels
	wxStaticText *st1 = new wxStaticText(panel, wxID_ANY, wxT("文件："), wxPoint(20, 18));
	wxStaticText *st2 = new wxStaticText(panel, wxID_ANY, wxT("目录："), wxPoint(20, 43));
	wxStaticText *st3 = new wxStaticText(panel, wxID_ANY, wxT("进度："), wxPoint(20, 68));
	m_check1 = new wxCheckBox(panel, wxID_ANY, wxT("生成解包记录"), wxPoint(70, 90));
	m_check1->SetValue(true);
	wxStaticText *st4 = new wxStaticText(panel, wxID_ANY, wxT("更多RGSSAD加密新方法见："), wxPoint(20, 115));
	wxHyperlinkCtrl *m_hyperlink = new wxHyperlinkCtrl(panel, ID_LINK1, wxT("http://blog.csdn.net/leexuany"), wxT("http://blog.csdn.net/leexuany"), wxPoint(200, 115));
	m_hyperlink->SetVisitedColour(wxColour(0, 0, 255));
	// create labels' font
	wxFont font1(10, wxDEFAULT, wxNORMAL, wxNORMAL);
	st1->SetFont(font1);
	st2->SetFont(font1);
	st3->SetFont(font1);
	st4->SetFont(font1);
	// create text control
	m_text1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 15), wxSize(280, 20));
	m_text2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 40), wxSize(280, 20));
	m_gauge1 = new wxGauge(panel, wxID_ANY, 10, wxPoint(70, 65), wxSize(280, 20));
	// create button
	wxButton *bt1 = new wxButton(panel, ID_BUTTON1, wxT("...."), wxPoint(365, 15), wxSize(40, 20));
	wxButton *bt2 = new wxButton(panel, ID_BUTTON2, wxT("...."), wxPoint(365, 40), wxSize(40, 20));
	m_bt3 = new wxButton(panel, ID_BUTTON3, wxT("解包"), wxPoint(365, 65), wxSize(40, 20));
	// connect event
	Connect(ID_BUTTON1, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(rgFrame::OnChoiceFile));
	Connect(ID_BUTTON2, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(rgFrame::OnChoiceDir));
	Connect(ID_BUTTON3, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(rgFrame::OnExtractor));

	m_text1->SetFocus();
	Centre();
}

void rgFrame::OnChoiceFile(wxCommandEvent& event)
{
	wxFileDialog File_Dialog(this, _T("Selecione o RGSSAD"), "", "", "*.rgssad", wxFD_DEFAULT_STYLE | wxFD_FILE_MUST_EXIST);

	if (File_Dialog.ShowModal() == wxID_OK)
	{
		m_text1->ChangeValue(File_Dialog.GetPath());
	}
}

void rgFrame::OnChoiceDir(wxCommandEvent& event)
{
	wxDirDialog Dir_Dialog(this, _T("Pasta de Saida"));

	if (Dir_Dialog.ShowModal() == wxID_OK)
	{
		m_text2->ChangeValue(Dir_Dialog.GetPath());
	}
}

void rgFrame::OnExtractor(wxCommandEvent& event)
{
	wxMessageDialog *Msg_Dialog = NULL;
	wxString infile,path;

	// Disable Button3
	m_bt3->Enable(false);
	// test File
	if (!wxFileExists(m_text1->GetValue()))
	{
		Msg_Dialog = new wxMessageDialog(NULL, wxT("RGSSAD文件不存在，请重新选择"), wxT("error"), wxOK | wxICON_ERROR);
		Msg_Dialog->ShowModal();
		delete Msg_Dialog;
		Msg_Dialog = NULL;
		m_bt3->Enable(true);
		return;
	}
	// test Dir
	if (!wxDirExists(m_text2->GetValue()))
	{
		Msg_Dialog = new wxMessageDialog(NULL, wxT("导出路径不存在，请重新选择"), wxT("error"), wxOK | wxICON_ERROR);
		Msg_Dialog->ShowModal();
		delete Msg_Dialog;
		Msg_Dialog = NULL;
		m_bt3->Enable(true);
		return;
	}

	// reset wxGaugeCtrl
	m_gauge1->SetValue(0);

	// get input file and path
	infile = m_text1->GetValue();
	path = m_text2->GetValue();
	if (path.Right(1) != _T("\\") && path.Right(1) != _T("/"))
	{
		path += _T("\\");
	}

	// invoke extract file function
	ExtractFile(infile, path, m_check1->GetValue());

	// 恢复"解包"按钮状态
	m_bt3->Enable(true);
}

void rgFrame::ExtractFile(wxString infile, wxString path, bool islog)
{
	wxMessageDialog *Msg_Dialog = NULL;
	unsigned char buf[1024];
	wxString outfile,logfile;
	SubInfo tmpInfo;
	vector<SubInfo> SubFileInfo;
	SubFileInfo.clear();
	unsigned long flag = 0, flag1 = 0;
	unsigned long magickey = 0xDEADCAFE;
	WCHAR wch_tmp[256];
	char endofline[] = {0x0D, 0x0A};

	wxFileInputStream rgssad_file(infile);
	wxFile sp_file;

	if (!rgssad_file.IsOk())
	{
		Msg_Dialog = new wxMessageDialog(NULL, wxT("打开RGSSAD文件失败"), wxT("error"), wxOK | wxICON_ERROR);
		Msg_Dialog->ShowModal();
		delete Msg_Dialog;
		Msg_Dialog = NULL;
		return;
	}
	rgssad_file.Read(&flag, 4);
	rgssad_file.Read(&flag1, 4);
	if (flag != 0x53534752 || flag1 != 0x01004441)
	{
		Msg_Dialog = new wxMessageDialog(NULL, wxT("这不是一个有效的RGSSAD文件"), wxT("error"), wxOK | wxICON_ERROR);
		Msg_Dialog->ShowModal();
		delete Msg_Dialog;
		Msg_Dialog = NULL;
		return;
	}

	logfile.Printf("%srgssad_sp.log", path);
	wxFileOutputStream *log_file = NULL;
	if(islog)
	{
		log_file = new wxFileOutputStream(logfile);
	}

	// 开始分析文件
	rgssad_file.Read(&tmpInfo.filenamesize, 4);
	while(!rgssad_file.Eof())
	{
		tmpInfo.filenamesize ^= magickey;
		magickey = magickey * 7 + 3;
		rgssad_file.Read(tmpInfo.filename, tmpInfo.filenamesize);
		for(unsigned long i = 0; i < tmpInfo.filenamesize; i++)
		{
			tmpInfo.filename[i] ^= magickey & 0xFF;
			magickey = magickey * 7 + 3;
		}
		tmpInfo.filename[i] = 0;
		MultiByteToWideChar(CP_UTF8, 0, tmpInfo.filename, -1, wch_tmp, 256);
		WideCharToMultiByte(CP_ACP, 0, wch_tmp, -1, tmpInfo.filename, 256, NULL, NULL);
		rgssad_file.Read(&tmpInfo.filesize, 4);
		tmpInfo.filesize ^= magickey;
		magickey = magickey * 7 + 3;
		tmpInfo.offset = rgssad_file.TellI();
		tmpInfo.magickey = magickey;
		SubFileInfo.push_back(tmpInfo);
		rgssad_file.SeekI(tmpInfo.filesize, wxFromCurrent);
		rgssad_file.Read(&tmpInfo.filenamesize, 4);
	}

	// reset wxGauge
	m_gauge1->SetRange(SubFileInfo.size());

	// 开始分解文件
	unsigned long leftsize;
	for(unsigned long i = 0; i < SubFileInfo.size(); i++)
	{
		outfile.Printf("%s%s", path, SubFileInfo[i].filename);
		sp_file.Open(outfile, wxFile::write);
		if(!sp_file.IsOpened())
		{
			check_path(outfile);
			sp_file.Open(outfile, wxFile::write);
			if(!sp_file.IsOpened())
			{
				if(log_file)
				{
					outfile += " failed.";
					log_file->Write(outfile, outfile.Len());
					log_file->Write(endofline, 2);
				}
				continue;
			}
		}
		rgssad_file.SeekI(SubFileInfo[i].offset, wxFromStart);
		magickey = SubFileInfo[i].magickey;
		leftsize = SubFileInfo[i].filesize;
		unsigned long j = 0;
		while(leftsize > 1023)
		{
			rgssad_file.Read(buf, 1024);
			for(j = 0; j < 1024; j+=4)
			{
				*(unsigned long *)(&buf[j]) ^= magickey;
				magickey = magickey * 7 + 3;
			}
			sp_file.Write(buf, 1024);
			leftsize -= 1024;
		}
		rgssad_file.Read(buf, leftsize);
		for(j = 0; j < leftsize; j+=4)
		{
			*(unsigned long *)(&buf[j]) ^= magickey;
			magickey = magickey * 7 + 3;
		}
		sp_file.Write(buf, leftsize);
		sp_file.Close();
		if(log_file)
		{
			outfile += " done.\n";
			log_file->Write(outfile, outfile.Len());
			log_file->Write(endofline, 2);
		}
		m_gauge1->SetValue(i);
	}
	m_gauge1->SetValue(i);
	delete log_file;
	Msg_Dialog = new wxMessageDialog(NULL, wxT("解包完毕"), wxT("haha"), wxOK | wxICON_INFORMATION);
	Msg_Dialog->ShowModal();
	delete Msg_Dialog;
}