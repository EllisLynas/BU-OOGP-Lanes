#pragma once

#include "GameObject.h"

class Line :	public GameObject
{
public:
	enum LineType { None, Blue, Green, Pink, Purple, Yellow, Finish };
	LineType m_LineType;
	bool m_LineCounted;

	enum LineOverlayColumn { None2, C1, C2, C3, C4, C5 } m_OverlayPosition;
	bool m_ScoreClaimed;

	Line();
	~Line();
};