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

class P_Node;
class Picture {
    friend std::ostream &operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture operator&(const Picture&, const Picture&);
    friend Picture operator|(const Picture&, const Picture&);

    friend class String_Pic;
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;

    public:
        Picture();
        Picture(const char *const *, int);
        Picture(const Picture&);
        ~Picture();

        Picture &operator=(const Picture&);

    private:
        Picture(P_Node*);
        int height() const;
        int width() const;
        void display(std::ostream&, int, int) const;
        P_Node *p;
};

class P_Node {
    friend class Picture;

    protected:
        P_Node();
        virtual ~P_Node();
        virtual int height() const = 0;
        virtual int width() const = 0;
        virtual void display(std::ostream&, int, int) const = 0;
        int max(const int, const int) const;

    private:
        int use;
};

class String_Pic : public P_Node {
    friend class Picture;
    String_Pic(const char *const *, int);
    ~String_Pic();
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;

    char **data;
    int size;
};

class Frame_Pic : public P_Node {
    friend Picture frame(const Picture&);
    Frame_Pic(const Picture&);
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture p;
};

class VCat_Pic : public P_Node {
    friend Picture operator&(const Picture&, const Picture&);
    VCat_Pic(const Picture&, const Picture&);
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture top, bottom;
};

class HCat_Pic : public P_Node {
    friend Picture operator|(const Picture&, const Picture&);
    HCat_Pic(const Picture&, const Picture&);
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture left, right;
};
