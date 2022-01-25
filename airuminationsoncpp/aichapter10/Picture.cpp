/*
 * =============================================================================
 *
 *       Filename:  Picture.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2022年01月24日 21时55分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <iostream>
#include <cstring>
#include "Picture.h"

Picture::Picture(const char *const *str, int n)
        : p(new String_Pic(str, n))
{

}

Picture::Picture(const Picture &orig)
        : p(orig.p)
{
    orig.p->use++;
}

Picture::Picture(P_Node *p_node)
        : p(p_node)
{

}

int Picture::height() const
{
    return p->height();
}

int Picture::width() const
{
    return p->width();
}

void Picture::display(std::ostream &o, int x, int y) const
{
    p->display(o, x, y);
}

std::ostream &operator<<(std::ostream &os, const Picture &picture)
{
    int ht = picture.height();

    for (int i = 0; i < ht; i++) {
        picture.display(os, i, 0);
        os << std::endl;
    }
    return os;
}

Picture::~Picture()
{
    if (--p->use == 0)
        delete p;
}

Picture &Picture::operator=(const Picture &orig)
{
    orig.p->use++;
    if (--p->use == 0)
        delete p;
    p = orig.p;
    return *this;
}

P_Node::P_Node()
        :use(1)
{
    /* Empty */
}

int P_Node::max(const int x, const int y) const
{
    return x > y ? x : y;
}

P_Node::~P_Node()
{
    /* Empty */
}

String_Pic::String_Pic(const char *const *p, int n)
        : data(new char *[n]), size(n)
{
    for (int i = 0; i < n; i++) {
        data[i] = new char[strlen(p[i]) + 1];
        strcpy(data[i], p[i]);
    }
}

int String_Pic::height() const
{
    return size;
}

int String_Pic::width() const
{
    int n = 0;

    for (int i = 0; i < size; i++)
        n = max(n, strlen(data[i]));
    return n;
}

static void pad(std::ostream &os, int x, int y)
{
    for (int i = x; i < y; i++)
        os << " ";
}

void String_Pic::display(std::ostream &os, int row, int width) const
{
    int start = 0;

    if (row >= 0 && row < height()) {
        os << data[row];
        start = strlen(data[row]);
    }

    pad(os, start, width);
}

String_Pic::~String_Pic()
{
    for (int i = 0; i < size; i++)
        delete [] data[i];
    delete [] data;
}

Frame_Pic::Frame_Pic(const Picture &pic)
        : p(pic)
{

}

int Frame_Pic::height() const
{
    return p.height() + 2;
}

int Frame_Pic::width() const
{
    return p.width() + 2;
}

void Frame_Pic::display(std::ostream &os, int row, int wd) const
{
    if (row < 0 || row >= height()) {
        pad(os, 0, wd);
    } else {
        if (row == 0 || row == height() - 1) {
            os << "+";
            int i = p.width();
            while (--i >= 0)
                os << "-";
            os << "+";
        } else {
            os << "|";
            p.display(os, row - 1, p.width());
            os << "|";
        }
        pad(os, width(), wd);
    }
}

Picture frame(const Picture &pic)
{
    return new Frame_Pic(pic);
}

VCat_Pic::VCat_Pic(const Picture &t, const Picture &b)
        : top(t), bottom(b)
{

}

Picture operator&(const Picture &t, const Picture &b)
{
    return new VCat_Pic(t, b);
}

int VCat_Pic::height() const
{
    return top.height() + bottom.height();
}

int VCat_Pic::width() const
{
    return max(top.width(), bottom.width());
}

void VCat_Pic::display(std::ostream &os, int row, int wd) const
{
    if (row >= 0 && row < top.height())
        top.display(os, row, wd);
    else if (row < top.height() + bottom.height())
        bottom.display(os, row - top.height(), wd);
    else
        pad(os, 0, wd);
}

HCat_Pic::HCat_Pic(const Picture &l, const Picture &r)
        : left(l), right(r)
{

}

Picture operator|(const Picture &l, const Picture &r)
{
    return new HCat_Pic(l, r);
}

int HCat_Pic::height() const
{
    return max(left.height(), right.height());
}

int HCat_Pic::width() const
{
    return left.width() + right.width();
}

void HCat_Pic::display(std::ostream &os, int row, int wd) const
{
    left.display(os, row, left.width());
    right.display(os, row, right.width());
    pad(os, width(), wd);
}
