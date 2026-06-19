#ifndef TIENICH_H
#define TIENICH_H

/* ===== Hang so dung chung cho toan chuong trinh ===== */
#define DO_DAI_DANHMUC 30
#define DO_DAI_GHICHU  100
#define DO_DAI_LOAI    5

/* Module Tien Ich
   Chua cac ham nhap du lieu an toan (luon kiem tra hop le truoc khi nhan)
   va kiem tra dieu kien bien dung chung cho ca chuong trinh.
   Day la tinh than "lap trinh phong ngua" duoc day o Bai 4. */

void   LamSachBoDem(void);
int    NhapSoNguyen(const char *thongBao, int gtMin, int gtMax);
double NhapSoThuc(const char *thongBao, double gtMin, double gtMax);
void   NhapChuoi(const char *thongBao, char *ketQua, int doDaiToiDa);
int    KiemTraNgayHopLe(int ngay, int thang, int nam);
void   NhapNgay(const char *thongBao, int *ngay, int *thang, int *nam);

#endif