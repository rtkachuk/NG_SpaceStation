#ifndef BASETOOL_H
#define BASETOOL_H

#include "baseitem.h"

enum toolMode {
	toolnomode,
	screwing,
	hammering,
	cutting,
	heating,
	welding
};

class BaseTool : public BaseItem
{
public:
	BaseTool();

	void setToolMode (toolMode mode) { m_mode = mode; }
	toolMode getToolMode() { return m_mode; }

	static toolMode detectToolMode(QString mode);

private:
	toolMode m_mode;
};

#endif // BASETOOL_H
