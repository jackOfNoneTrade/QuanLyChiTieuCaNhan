#ifndef GIAODICH_H
#define GIAODICH_H

#include "tienich.h"

#define TEN_FILE_GIAODICH "data/giaodich.txt"

/* Cau truc luu 1 giao dich thu/chi, dong thoi la 1 nut cua
   danh sach lien ket don */
typedef struct GiaoDich {
    int    id;
    int    ngay, thang, nam;
    char   loai[DO_DAI_LOAI];        /* "Thu" hoac "Chi" */
    char   danhMuc[DO_DAI_DANHMUC];
    double soTien;
    char   ghiChu[DO_DAI_GHICHU];
    struct GiaoDich *tiep;
} GiaoDich;

/* --- CRUD --- */
void      ThemGiaoDich(GiaoDich **dauDS);
void      SuaGiaoDich(GiaoDich *dauDS);          /* tim nut roi sua tai cho */
void      XoaGiaoDich(GiaoDich **dauDS);
GiaoDich* TimGiaoDich(GiaoDich *dauDS, int id);  /* tra ve ptr co the sua */

/* --- Ham tro giup (chi doc) --- */
int  LayIDLonNhat(const GiaoDich *dauDS);
int  DemSoGiaoDich(const GiaoDich *dauDS);
void InDanhSachGiaoDich(const GiaoDich *dauDS);

/* --- Bo nho --- */
void GiaiPhongDanhSach(GiaoDich **dauDS);

/* --- Ham cong khai de taodata dung: them nut da cap phat san vao cuoi DS --- */
void ThemGiaoDichTruc(GiaoDich **dauDS, GiaoDich *gd);

/* --- File I/O --- */
int    DocFileGiaoDich(GiaoDich **dauDS);
int    GhiFileGiaoDich(const GiaoDich *dauDS);

/* --- Thong ke (chi doc) --- */
double TinhTongTheoLoai(const GiaoDich *dauDS, const char *loai,
                        int ngay, int thang, int nam);
double TinhTongTheoDanhMuc(const GiaoDich *dauDS, const char *danhMuc,
                           int thang, int nam);
double TinhSoDu(const GiaoDich *dauDS, int thang, int nam);

/* --- Sap xep (sua du lieu tai cho) --- */
void SapXepTheoSoTien(GiaoDich *dauDS, int tangDan);

#endif