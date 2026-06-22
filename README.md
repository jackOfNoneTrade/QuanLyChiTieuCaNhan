# Chương Trình Quản Lý Chi Tiêu Cá Nhân

> **Môn:** Kỹ Thuật Lập Trình - MI3310 | ĐH Bách Khoa Hà Nội  
> **GVHD:** Vũ Thành Nam  
> **Nhóm 14:** Nguyễn Huy Đức (202418871) · Đặng Tuấn Đạt (202418867)

![Language](https://img.shields.io/badge/Language-C-blue)
![Build](https://img.shields.io/badge/Build-g%2B%2B-green)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)
![DataStructure](https://img.shields.io/badge/Data%20Structure-Linked%20List-orange)

Ứng dụng chạy trên giao diện dòng lệnh (CLI), cho phép ghi chép các khoản thu/chi hằng ngày theo danh mục, thiết lập hạn mức ngân sách theo tháng, xem báo cáo thống kê dạng biểu đồ ASCII và cảnh báo khi vượt ngân sách. Dữ liệu được lưu vào file `.txt` và tự động nạp lại ở lần chạy sau.

---

## Tính năng

- **Ghi chép giao dịch:**
  - Thêm, sửa, xóa các khoản **Thu** và **Chi**.
  - Mỗi giao dịch gồm: ngày/tháng/năm, danh mục, số tiền, loại (thu/chi) và ghi chú.
  - ID tự động sinh (`IDLonNhat + 1`), không bao giờ trùng trong một phiên chạy.
  - Khi thêm hoặc sửa giao dịch, chương trình hiển thị **danh sách danh mục có sẵn** từ ngân sách (kèm số thứ tự) để người dùng chọn bằng số thay vì gõ tay. Vẫn có thể nhập danh mục mới nếu chọn `[0]`.
- **Quản lý ngân sách:** Thêm và cập nhật hạn mức chi tiêu cho từng danh mục theo tháng/năm. Tự cập nhật nếu (danh mục + tháng + năm) đã tồn tại, nếu chưa thì tạo mới. Danh mục trong ngân sách là nguồn gợi ý cho phần nhập giao dịch.
- **Thống kê & báo cáo:**
  - Tổng hợp thu/chi và số dư theo tháng/năm.
  - Hiển thị tỷ lệ chi tiêu theo từng danh mục kèm biểu đồ ASCII (mỗi 2% = 1 ký tự `#`).
  - Cảnh báo khi số tiền đã chi vượt hạn mức ngân sách đã thiết lập.
- **Sắp xếp:** Sắp xếp danh sách giao dịch tăng dần hoặc giảm dần theo số tiền (Selection Sort).
- **Dữ liệu mẫu:** Tích hợp sẵn 3 kịch bản kiểm thử có thể nạp từ menu, phục vụ demo và kiểm thử các trường hợp biên.
- **Lưu trữ dữ liệu:** Tự động đọc dữ liệu khi khởi động; tự bảo vệ khi file bị hỏng (bỏ qua dòng sai định dạng, không crash). Ghi xuống file khi chọn [0] Lưu và thoát.

---

## Thiết kế / Kiến trúc

Chương trình được tổ chức theo hướng **module hóa**, tách biệt dữ liệu, logic xử lý và giao diện. Mỗi module chỉ biết những gì nó cần - không có biến toàn cục, không có phụ thuộc vòng tròn giữa các module.

```
main (điều phối, không xử lý nghiệp vụ)
 ├── tienich   — lớp nền: nhập liệu an toàn, kiểm tra ngày hợp lệ
 ├── giaodich  — CRUD, thống kê, sắp xếp, file I/O giao dịch
 ├── ngansach  — CRUD, file I/O ngân sách, cung cấp danh mục cho giaodich
 ├── baocao    — báo cáo tổng hợp, biểu đồ ASCII, cảnh báo vượt hạn mức
 └── taodata   — sinh dữ liệu mẫu (3 kịch bản kiểm thử)
```

**Thứ tự phụ thuộc giữa các module** (module bên trái chỉ được `#include` module bên phải):

| Module | Phụ thuộc vào |
|---|---|
| `tienich` | (không phụ thuộc — lớp nền) |
| `ngansach` | `tienich` |
| `giaodich` | `tienich`, `ngansach` |
| `baocao` | `giaodich`, `ngansach` |
| `taodata` | `giaodich`, `ngansach` |
| `main` | tất cả các module trên |

`giaodich` phụ thuộc vào `ngansach` vì khi nhập giao dịch, module này cần lấy danh sách danh mục duy nhất từ ngân sách (`LayDanhMucDuy`) để hiển thị cho người dùng chọn.

**Cấu trúc dữ liệu:** Danh sách liên kết đơn (`GiaoDich.tiep`, `NganSach.tiep`) — cho phép số lượng phần tử tăng giảm linh hoạt khi chạy mà không cần biết trước số lượng tối đa. Đánh đổi là mọi tìm kiếm phải duyệt tuần tự O(n). Mỗi nút được cấp phát bằng `malloc()` và phải `free()` khi không dùng — đảm bảo bằng `GiaiPhongDanhSach()` / `GiaiPhongNganSach()` ngay trước `return 0`.

**Số thứ tự trong ngân sách:** STT chỉ là biến đếm trong vòng lặp khi in, không lưu vào struct. Sau khi xóa một phần tử, gọi lại hàm in sẽ tự động hiển thị đúng thứ tự mới mà không cần cập nhật gì trong dữ liệu.

**Thuật toán sắp xếp:** Selection Sort hoán vị **dữ liệu** (không hoán vị con trỏ) — giữ nguyên toàn bộ cấu trúc liên kết, chỉ copy nội dung các trường giữa hai nút. Đơn giản và an toàn hơn việc phải tìm và sửa lại con trỏ của các nút trước; phù hợp với quy mô vài trăm giao dịch.

**Tránh lặp code:** `ThemGiaoDichTruc()` / `ThemNganSachTruc()` là hàm chèn-cuối dùng chung giữa nhập tay (Menu 1) và sinh dữ liệu mẫu (`taodata.cpp`), tránh viết lại logic duyệt tới cuối danh sách ở hai nơi.

---

## Cấu trúc thư mục

```
quanlychitieu/
├── include/                     # Header files — khai báo kiểu dữ liệu và hàm
│   ├── tienich.h                # Hằng số dùng chung + khai báo nhập liệu
│   ├── giaodich.h               # Kiểu GiaoDich (DSLK đơn) + khai báo CRUD
│   ├── ngansach.h               # Kiểu NganSach (DSLK đơn) + khai báo CRUD
│   ├── baocao.h                 # Khai báo hàm báo cáo, biểu đồ ASCII
│   └── taodata.h                # Khai báo hàm sinh dữ liệu mẫu
├── src/                         # Source files — cài đặt logic
│   ├── main.cpp                 # Điểm vào duy nhất — điều phối, không xử lý nghiệp vụ
│   ├── tienich.cpp              # Nhập liệu an toàn, kiểm tra ngày hợp lệ
│   ├── giaodich.cpp             # CRUD, thống kê, sắp xếp, file I/O giao dịch
│   ├── ngansach.cpp             # CRUD, file I/O ngân sách
│   ├── baocao.cpp               # Báo cáo tổng hợp, biểu đồ ASCII, cảnh báo
│   └── taodata.cpp              # Sinh dữ liệu mẫu (3 kịch bản)
├── data/                        # File dữ liệu — tự động tạo/cập nhật khi chạy
│   ├── giaodich.txt             # Danh sách giao dịch thu/chi
│   └── ngansach.txt             # Danh sách ngân sách theo danh mục
├── build/                       # Output biên dịch (bị .gitignore, không push lên Git)
├── Makefile                     # Build cho Linux / macOS
├── build.bat                    # Build cho Windows
├── .gitignore
└── README.md
```

---

## Yêu cầu hệ thống

Chương trình yêu cầu trình biên dịch **g++ (GCC ≥ 7)**. Không cần cài thêm thư viện ngoài — chỉ dùng thư viện chuẩn C (`stdio.h`, `stdlib.h`, `string.h`).

```bash
g++ --version
```

> **Vì sao file `.cpp` nhưng lại gọi là "code C"?** Toàn bộ logic được viết bằng C thuần (không dùng class, không dùng `new`/`delete`, không dùng STL). Đuôi file là `.cpp` và dùng `g++` là lựa chọn của nhóm để tận dụng một số tiện ích biên dịch, **không phải vì code có cú pháp C++**. Nếu đổi đuôi sang `.c` và biên dịch bằng `gcc`, chương trình vẫn chạy đúng không cần sửa gì.

---

## Biên dịch và Chạy

### Bước 1: Sao chép dự án (Clone Repository)

```bash
git clone <repository-url>
cd quanlychitieu
```

### Bước 2: Biên dịch chương trình

**Linux / macOS:**

```bash
make           # chỉ biên dịch
make run       # biên dịch + chạy ngay
make clean     # xóa file biên dịch trong build/
```

**Windows:**

```bat
build.bat
```

> **Lưu ý Windows:** `build.bat` sẽ tự động chạy chương trình ngay sau khi biên dịch thành công — không cần chạy thêm bước 3 nếu dùng script này.

### Bước 3: Chạy chương trình

**Linux / macOS:**
```bash
./build/quanlychitieu.exe
```

**Windows:**
```bat
build\quanlychitieu.exe
```

> **Lưu ý:** Luôn chạy từ **thư mục gốc** của project (cùng cấp với thư mục `data/`). Nếu chạy từ thư mục khác, chương trình sẽ không tìm được file dữ liệu (dùng đường dẫn tương đối `data/giaodich.txt`).

---

## Hướng dẫn sử dụng nhanh

Sau khi chạy chương trình, menu chính sẽ hiển thị:

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

Nhập số tương ứng và làm theo hướng dẫn nhập liệu trên màn hình.

**Luồng sử dụng khuyến nghị:** Nên thiết lập ngân sách (Menu 6) trước khi thêm giao dịch (Menu 1). Khi đó, lúc nhập danh mục cho giao dịch, chương trình tự động hiển thị danh mục có sẵn để chọn bằng số:

```
Danh muc hien co trong ngan sach:
  [1] An uong
  [2] Di chuyen
  [3] Hoc tap
  [0] Nhap danh muc moi
Chon danh muc:
```

Nếu chưa có ngân sách nào, ô nhập danh mục chuyển sang chế độ gõ tay tự do như bình thường.

**Tạo dữ liệu mẫu (Menu 9):** Chọn một trong 3 kịch bản để nạp dữ liệu sẵn mà không cần nhập tay:

| Kịch bản | Mô tả | Số lượng | Mục đích kiểm thử |
|---|---|---|---|
| **1. Sinh viên** | 3 tháng (4–5–6/2025) | 50 GD, 10 NS | Tháng 5/2025 có **3 danh mục vượt ngân sách** → kiểm tra cảnh báo (Menu 8 → 5/2025). Tháng 6 **không vượt** → kiểm tra trường hợp không có cảnh báo. |
| **2. Đi làm full-time** | 1 tháng (1/2025) | 13 GD, 5 NS | Tất cả danh mục **trong hạn mức** → kiểm tra báo cáo khi không có cảnh báo (Menu 8 → 1/2025). |
| **3. Tối thiểu** | 2 bản ghi (3/2025) | 2 GD, 1 NS | 1 danh mục **vượt mạnh** (chi 4,8 triệu / hạn mức 3 triệu) → kiểm tra điều kiện biên với dữ liệu rất ít. |

Chọn kịch bản mới sẽ xóa dữ liệu cũ trong bộ nhớ — dữ liệu cũ chỉ mất thật nếu sau đó chọn **[0] Lưu và thoát**.

---

## Ghi chú

- **Dữ liệu chỉ lưu khi chọn [0] Lưu và thoát** — tắt cửa sổ đột ngột sẽ mất thay đổi vì dữ liệu đang trong bộ nhớ (DSLK), chưa được ghi xuống file.
- **Lần đầu chạy** khi chưa có file: chương trình tự bắt đầu với danh sách rỗng, không báo lỗi.
- **Không chạy hai instance** cùng lúc trên cùng thư mục — cả hai sẽ ghi đè lên file dữ liệu khi thoát, gây mất dữ liệu của bên thoát trước.
- **Định dạng file dữ liệu:** phân tách bằng `|`, đọc bằng `fgets()` từng dòng + phân tích bằng `sscanf()`. Nếu sửa tay file và làm sai định dạng, chương trình tự bỏ qua dòng đó mà không crash.
