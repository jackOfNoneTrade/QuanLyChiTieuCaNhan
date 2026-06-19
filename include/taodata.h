#ifndef TAODATA_H
#define TAODATA_H

#include "giaodich.h"
#include "ngansach.h"

/* Hoi nguoi dung lua chon kich ban, sinh du lieu mau vao DS trong bo nho.
   DS cu se bi xoa truoc khi nap moi. Viec ghi file do main quan ly. */
void TaoDuLieuMau(GiaoDich **dsGD, NganSach **dsNS);

#endif