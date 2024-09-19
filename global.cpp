#include "global.h"

QString gate_url_prefix = "";

std::function<void(QWidget*)> repolish = [](QWidget* w){
    w->style()->unpolish(w); // 卸掉polish
    w->style()->polish(w); // 重新加载polish
};
