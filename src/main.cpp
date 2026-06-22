#include <stdio.h>
#include "tienich.h"
#include "giaodich.h"
#include "ngansach.h"
#include "baocao.h"
#include "taodata.h"

/* So lua chon toi da cua menu -- chinh o day neu them/xoa option */
#define MENU_MAX 9

/* Nhiem vu : In menu lua chon tac vu ra man hinh.
   Dau vao  : khong co
   Dau ra   : khong co */
static void HienThiMenu(void) {
    printf("\n--------------------- MENU ---------------------\n");
    printf("1. Them giao dich\n");
    printf("2. Sua giao dich\n");
    printf("3. Xoa giao dich\n");
    printf("4. Xem danh sach giao dich\n");
    printf("5. Sap xep giao dich theo so tien\n");
    printf("6. Thiet lap ngan sach cho danh muc\n");
    printf("7. Xem danh sach ngan sach\n");
    printf("8. Xem bao cao tong hop theo thang\n");
    printf("9. Tao du lieu mau (kiem thu)\n");
    printf("0. Luu va thoat\n");
    printf("-------------------------------------------------\n");
}

/* Nhiem vu : Ham main -- doc file khi khoi dong, dieu phoi vong lap menu,
              ghi file va giai phong bo nho truoc khi thoat.
              Khong tu xu ly nghiep vu -- chi goi cac ham chuyen biet.
   Dau vao  : khong co
   Dau ra   : 0 neu chuong trinh ket thuc binh thuong */
int main(void) {
    GiaoDich *dsGiaoDich = NULL;
    NganSach *dsNganSach = NULL;

    DocFileGiaoDich(&dsGiaoDich);
    DocFileNganSach(&dsNganSach);

    printf("====================================================\n");
    printf("     CHUONG TRINH QUAN LY CHI TIEU CA NHAN\n");
    printf("====================================================\n");
    printf("Da nap %d giao dich va %d ngan sach tu file.\n",
           DemSoGiaoDich(dsGiaoDich), DemSoNganSach(dsNganSach));

    int luaChon;
    do {
        HienThiMenu();
        luaChon = NhapSoNguyen("Lua chon cua ban: ", 0, MENU_MAX);

        switch (luaChon) {
            case 1: ThemGiaoDich(&dsGiaoDich);                              break;
            case 2: SuaGiaoDich(dsGiaoDich);                                break;
            case 3: XoaGiaoDich(&dsGiaoDich);                               break;
            case 4: InDanhSachGiaoDich(dsGiaoDich);                         break;
            case 5: {
                int tangDan = NhapSoNguyen("Tang dan(1) hay giam dan(0)? ", 0, 1);
                SapXepTheoSoTien(dsGiaoDich, tangDan);
                CapNhatIDTuanTu(dsGiaoDich);   /* cap lai ID theo thu tu moi */
                printf("Da sap xep xong. ID da duoc cap nhat lai.\n");
                InDanhSachGiaoDich(dsGiaoDich);
                break;
            }
            case 6: ThietLapNganSach(&dsNganSach);                          break;
            case 7: InDanhSachNganSach(dsNganSach);                         break;
            case 8: {
                int thang = NhapSoNguyen("Thang (1-12): ", 1, 12);
                int nam   = NhapSoNguyen("Nam (2000-2100): ", 2000, 2100);
                BaoCaoTongHop(dsGiaoDich, dsNganSach, thang, nam);
                break;
            }
            case 9: TaoDuLieuMau(&dsGiaoDich, &dsNganSach);                break;
            case 0: printf("Dang luu du lieu va thoat...\n");               break;
        }
        /* NhapSoNguyen da rang buoc input ve [0, MENU_MAX],
           moi gia tri deu co case xu ly -- khong can default. */
    } while (luaChon != 0);

    /* Ghi file chi duoc goi tai day -- khong o bat ky ham nao khac */
    GhiFileGiaoDich(dsGiaoDich);
    GhiFileNganSach(dsNganSach);

    GiaiPhongDanhSach(&dsGiaoDich);
    GiaiPhongNganSach(&dsNganSach);

    printf("Da luu du lieu. Tam biet!\n");
    return 0;
}