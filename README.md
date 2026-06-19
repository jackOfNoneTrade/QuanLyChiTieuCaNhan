# Quản Lý Chi Tiêu Cá Nhân

**Đề tài:** Hệ thống quản lý thu chi cá nhân sử dụng danh sách liên kết đơn  
**Môn:** Kỹ Thuật Lập Trình — MI3310 | ĐH Bách Khoa Hà Nội  

---

## Yêu cầu hệ thống

- **g++** (GCC ≥ 7) — biên dịch code C chuẩn bằng g++
- Không cần cài thêm thư viện ngoài (chỉ dùng thư viện chuẩn C)

Kiểm tra phiên bản g++:
```bash
g++ --version
```

---

## Cách chạy chương trình

### Linux / macOS

```bash
cd quanlychitieu
make        # biên dịch
make run    # biên dịch + chạy ngay
```

### Windows

```bat
cd quanlychitieu
build.bat
```

> ⚠️ **Quan trọng:** Luôn chạy chương trình từ **thư mục gốc** của project (cùng cấp với thư mục `data/`). Nếu chạy từ thư mục khác, chương trình sẽ không tìm được file dữ liệu.

---

## Tạo dữ liệu mẫu (tùy chọn)

Muốn có sẵn dữ liệu khi mở chương trình lần đầu, vào **Menu → chọn 9**, sau đó chọn một trong 3 kịch bản:

| Kịch bản | Mô tả | Số lượng | Điểm kiểm thử |
|---|---|---|---|
| **1. Sinh viên** | 3 tháng (4–5–6/2025), có tháng vượt ngân sách | 50 GD, 10 NS | Menu 8 → tháng 5/2025 |
| **2. Đi làm full-time** | 1 tháng (1/2025), tất cả trong hạn mức | 13 GD, 5 NS | Menu 8 → tháng 1/2025 |
| **3. Tối thiểu** | 2 bản ghi, kiểm tra điều kiện biên | 2 GD, 1 NS | Menu 8 → tháng 3/2025 |

---

## Cấu trúc dự án

```
quanlychitieu/
├── include/                     # Header files — khai báo kiểu dữ liệu và hàm
│   ├── tienich.h                # Hằng số dùng chung + khai báo nhập liệu
│   ├── giaodich.h               # Kiểu GiaoDich (DSLK đơn) + khai báo CRUD
│   ├── ngansach.h               # Kiểu NganSach (DSLK đơn) + khai báo CRUD
│   ├── baocao.h                 # Khai báo hàm báo cáo, biểu đồ ASCII
│   └── taodata.h                # Khai báo hàm sinh dữ liệu mẫu
│
├── src/                         # Source files — cài đặt logic
│   ├── main.cpp                 # Điểm vào duy nhất — điều phối, không xử lý nghiệp vụ
│   ├── tienich.cpp              # Nhập liệu an toàn, kiểm tra ngày hợp lệ
│   ├── giaodich.cpp             # CRUD, thống kê, sắp xếp, file I/O giao dịch
│   ├── ngansach.cpp             # CRUD, file I/O ngân sách
│   ├── baocao.cpp               # Báo cáo tổng hợp, biểu đồ ASCII, cảnh báo
│   └── taodata.cpp              # Sinh dữ liệu mẫu (3 kịch bản)
│
├── data/                        # File dữ liệu — tự động tạo/cập nhật khi chạy
│   ├── giaodich.txt             # Danh sách giao dịch thu/chi
│   └── ngansach.txt             # Danh sách ngân sách theo danh mục
│
├── build/                       # Output biên dịch (bị .gitignore, không push lên Git)
├── Makefile                     # Build cho Linux / macOS
├── build.bat                    # Build cho Windows
├── .gitignore
└── README.md
```

---

## Kiến trúc module

```
main (điều phối, không xử lý nghiệp vụ)
 ├── tienich   — lớp nền: nhập liệu an toàn, kiểm tra ngày hợp lệ
 ├── giaodich  — CRUD, thống kê, sắp xếp, file I/O giao dịch
 ├── ngansach  — CRUD, file I/O ngân sách
 ├── baocao    — báo cáo tổng hợp, biểu đồ ASCII, cảnh báo vượt hạn mức
 └── taodata   — sinh dữ liệu mẫu (3 kịch bản kiểm thử)
```

Nguyên tắc **top-down, không có biến toàn cục**: mỗi module chỉ biết những gì nó cần; `main` chỉ đọc file, gọi menu, ghi file rồi thoát.

---

## Hướng dẫn sử dụng

Sau khi chạy chương trình, menu hiển thị:

```
====================================================
     CHUONG TRINH QUAN LY CHI TIEU CA NHAN
====================================================
Da nap 50 giao dich va 10 ngan sach tu file.

--------------------- MENU ---------------------
1. Them giao dich
2. Sua giao dich
3. Xoa giao dich
4. Xem danh sach giao dich
5. Sap xep giao dich theo so tien
6. Thiet lap ngan sach cho danh muc
7. Xem danh sach ngan sach
8. Xem bao cao tong hop theo thang
9. Tao du lieu mau (kiem thu)
0. Luu va thoat
-------------------------------------------------
```

| Chức năng | Mô tả |
|---|---|
| **[1] Thêm giao dịch** | Nhập ngày, loại (Thu/Chi), danh mục, số tiền, ghi chú. ID tự động sinh. |
| **[2] Sửa giao dịch** | Hiển thị danh sách, nhập ID, nhấn 1 để giữ nguyên từng trường. |
| **[3] Xóa giao dịch** | Xác nhận bằng ID trước khi xóa, tự động giải phóng bộ nhớ. |
| **[4] Xem danh sách** | In toàn bộ giao dịch kèm tổng số bản ghi. |
| **[5] Sắp xếp** | Chọn tăng dần hoặc giảm dần theo số tiền (Selection Sort). |
| **[6] Thiết lập ngân sách** | Đặt hạn mức chi cho từng danh mục theo tháng/năm. Tự cập nhật nếu đã tồn tại. |
| **[7] Xem ngân sách** | Danh sách hạn mức đã thiết lập. |
| **[8] Báo cáo tổng hợp** | Tổng thu/chi/số dư + biểu đồ ASCII tỷ lệ % + cảnh báo vượt hạn mức. |
| **[9] Dữ liệu mẫu** | Chọn 1 trong 3 kịch bản kiểm thử, xóa dữ liệu cũ và nạp mới vào bộ nhớ. |
| **[0] Lưu và thoát** | Ghi toàn bộ dữ liệu xuống file rồi giải phóng bộ nhớ. |

### Ví dụ output Báo cáo tổng hợp (Menu 8)

```
========== BAO CAO TONG HOP THANG 5/2025 ==========
Tong thu : 9900000.00
Tong chi : 2975000.00
So du    : 6925000.00

--- TY LE CHI TIEU THANG 5/2025 (tong chi: 2975000.00) ---
An uong         50.59% #########################
Hoc tap         33.61% ################
Giai tri        16.13% ########
Di chuyen        9.75% ####
Sinh hoat       13.11% ######

--- CANH BAO NGAN SACH THANG 5/2025 ---
VUOT: 'An uong'  da chi 1505000.00 / han muc  600000.00 (vuot  905000.00)
VUOT: 'Hoc tap'  da chi 1000000.00 / han muc  700000.00 (vuot  300000.00)
VUOT: 'Giai tri' da chi  480000.00 / han muc  400000.00 (vuot   80000.00)
===================================================
```

---

## Định dạng file dữ liệu

Dữ liệu được lưu dưới dạng text thuần, phân tách bằng `|` để tránh lỗi khi nội dung có khoảng trắng.

**`data/giaodich.txt`**
```
id|ngay|thang|nam|loai|danhMuc|soTien|ghiChu
1|1|4|2025|Thu|Luong|8000000.00|Luong thang 4
4|2|4|2025|Chi|An uong|85000.00|Com trua van phong
```

**`data/ngansach.txt`**
```
danhMuc|thang|nam|hanMuc
An uong|5|2025|600000.00
Di chuyen|5|2025|300000.00
```

---

## Các điểm kỹ thuật nổi bật

| Chủ đề | Cài đặt cụ thể |
|---|---|
| **DSLK đơn** | `GiaoDich.tiep` và `NganSach.tiep` — thêm cuối, xóa bất kỳ, duyệt tuyến tính |
| **Selection Sort** | `SapXepTheoSoTien`: 2 vòng for lồng nhau, hoán vị dữ liệu (không đổi con trỏ) |
| **Lập trình phòng ngừa** | `NhapSoNguyen`, `NhapSoThuc`, `NhapNgay` đều có `while(1)` + kiểm tra biên + `LamSachBoDem()` |
| **Hàm `static` nội bộ** | `InMotGiaoDich`, `NhapLoai`, `NhapDanhMuc` chỉ dùng trong module, ẩn với ngoài |
| **File I/O** | `sscanf` với format `%99[^\n]` đọc được ghi chú có khoảng trắng |
| **Không memory leak** | `GiaiPhongDanhSach` + `GiaiPhongNganSach` được gọi trong `main` trước khi `return 0` |

---

## Lưu ý quan trọng

- **Dữ liệu chỉ lưu khi chọn [0] Lưu và thoát** — tắt cửa sổ đột ngột sẽ mất thay đổi.
- **Lần đầu chạy** khi chưa có file: chương trình tự bắt đầu với danh sách rỗng, không báo lỗi.
- **Xóa toàn bộ dữ liệu:** xóa nội dung hai file trong thư mục `data/` hoặc chọn kịch bản mới ở Menu 9.
- **Mã ID giao dịch** được sinh tự động bằng `IDLonNhat + 1`, không bao giờ trùng trong một phiên.
- **Không chạy hai instance** chương trình cùng lúc trên cùng thư mục — có thể gây xung đột file.