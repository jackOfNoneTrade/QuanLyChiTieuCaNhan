#ifndef BAOCAO_H
#define BAOCAO_H

#include "giaodich.h"
#include "ngansach.h"

void ThongKeTyLeDanhMuc(const GiaoDich *dauDS, int thang, int nam);
void KiemTraVuotNganSach(const GiaoDich *dsGD, const NganSach *dsNS,
                         int thang, int nam);
void BaoCaoTongHop(const GiaoDich *dsGD, const NganSach *dsNS,
                   int thang, int nam);

#endif