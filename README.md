# Quản Lý Chi Tiêu Cá Nhân

**Đề tài:** Hệ thống quản lý thu chi cá nhân sử dụng danh sách liên kết đơn
**Môn:** Kỹ Thuật Lập Trình - MI3310 | ĐH Bách Khoa Hà Nội
**GVHD:** Vũ Thành Nam
**Nhóm 14:**
- Nguyễn Huy Đức - 202418871 
- Đặng Tuấn Đạt - 202418867 

---

## Yêu cầu hệ thống

- **g++** (GCC ≥ 7)
- Không cần cài thêm thư viện ngoài (chỉ dùng thư viện chuẩn C: `stdio.h`, `stdlib.h`, `string.h`)

Kiểm tra phiên bản g++:
```bash
g++ --version
```

> 💡 **Vì sao file `.cpp` nhưng lại gọi là "code C"?**
> Toàn bộ logic được viết bằng C thuần (không dùng class, không dùng `new`/`delete`, không dùng STL...). Sở dĩ đuôi file là `.cpp` và biên dịch bằng `g++` thay vì `gcc` là lựa chọn của nhóm để tận dụng một số tiện ích biên dịch của g++, **không phải vì code có cú pháp C++**. Nếu đổi đuôi sang `.c` và biên dịch bằng `gcc`, chương trình vẫn chạy đúng không cần sửa gì.

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

> ⚠️ **Lưu ý:** Luôn chạy chương trình từ **thư mục gốc** của project (cùng cấp với thư mục `data/`). Nếu chạy từ thư mục khác, chương trình sẽ không tìm được file dữ liệu (nó dùng đường dẫn tương đối `data/giaodich.txt`).

---

## Tạo dữ liệu mẫu (tùy chọn)

Muốn có sẵn dữ liệu khi mở chương trình lần đầu (để không phải nhập tay), vào **Menu → chọn 9**, sau đó chọn một trong 3 kịch bản. Mỗi kịch bản phục vụ một mục đích kiểm thử khác nhau:

| Kịch bản | Mô tả | Số lượng | Mục đích kiểm thử |
|---|---|---|---|
| **1. Sinh viên** | 3 tháng (4–5–6/2025) | 50 GD, 10 NS | Tháng 5/2025 có **3 danh mục vượt ngân sách** (Ăn uống, Học tập, Giải trí) → kiểm tra cảnh báo vượt hạn mức (Menu 8 → tháng 5/2025). Tháng 6 thì **không vượt** → kiểm tra trường hợp không có cảnh báo. |
| **2. Đi làm full-time** | 1 tháng (1/2025) | 13 GD, 5 NS | Tất cả danh mục **trong hạn mức** → kiểm tra báo cáo khi không có cảnh báo nào (Menu 8 → tháng 1/2025). |
| **3. Tối thiểu** | 2 bản ghi (3/2025) | 2 GD, 1 NS | Số dư gần 0, 1 danh mục **vượt mạnh** (chi 4,8 triệu / hạn mức 3 triệu) → kiểm tra điều kiện biên với dữ liệu rất ít (Menu 8 → tháng 3/2025). |

Chọn kịch bản mới sẽ **xóa dữ liệu cũ trong bộ nhớ** và nạp dữ liệu mới — dữ liệu cũ chỉ mất thật nếu sau đó bạn chọn [0] Lưu và thoát.

---

## Cấu trúc dự án

```
quanlychitieu/
├── include/                     # Header files - khai báo kiểu dữ liệu và hàm
│   ├── tienich.h                # Hằng số dùng chung + khai báo nhập liệu
│   ├── giaodich.h               # Kiểu GiaoDich (DSLK đơn) + khai báo CRUD
│   ├── ngansach.h               # Kiểu NganSach (DSLK đơn) + khai báo CRUD
│   ├── baocao.h                 # Khai báo hàm báo cáo, biểu đồ ASCII
│   └── taodata.h                # Khai báo hàm sinh dữ liệu mẫu
│
├── src/                         # Source files - cài đặt logic
│   ├── main.cpp                 # Điểm vào duy nhất - điều phối, không xử lý nghiệp vụ
│   ├── tienich.cpp              # Nhập liệu an toàn, kiểm tra ngày hợp lệ
│   ├── giaodich.cpp             # CRUD, thống kê, sắp xếp, file I/O giao dịch
│   ├── ngansach.cpp             # CRUD, file I/O ngân sách
│   ├── baocao.cpp               # Báo cáo tổng hợp, biểu đồ ASCII, cảnh báo
│   └── taodata.cpp              # Sinh dữ liệu mẫu (3 kịch bản)
│
├── data/                        # File dữ liệu - tự động tạo/cập nhật khi chạy
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
 ├── tienich   - lớp nền: nhập liệu an toàn, kiểm tra ngày hợp lệ
 ├── giaodich  - CRUD, thống kê, sắp xếp, file I/O giao dịch
 ├── ngansach  - CRUD, file I/O ngân sách
 ├── baocao    - báo cáo tổng hợp, biểu đồ ASCII, cảnh báo vượt hạn mức
 └── taodata   - sinh dữ liệu mẫu (3 kịch bản kiểm thử)
```

**Thứ tự phụ thuộc giữa các module** (module bên trái chỉ được `#include` module bên phải, không được làm ngược lại):

| Module | Phụ thuộc vào |
|---|---|
| `tienich` | (không phụ thuộc module nào — lớp nền) |
| `giaodich` | `tienich` |
| `ngansach` | `tienich` |
| `baocao` | `giaodich`, `ngansach` |
| `taodata` | `giaodich`, `ngansach` |
| `main` | tất cả các module trên |

Lý do bắt buộc theo chiều này: nếu cho phép include ngược (ví dụ `tienich` include `giaodich`), code sẽ phụ thuộc vòng tròn, rất khó bảo trì và không thể build độc lập từng module.

**Nguyên tắc top-down, không có biến toàn cục:** mỗi module chỉ biết những gì nó cần - `baocao` không tự ý sửa danh sách giao dịch, nó chỉ đọc qua các hàm thống kê mà `giaodich` cung cấp. `main` chỉ đọc file, gọi menu, ghi file rồi thoát; **không tự xử lý nghiệp vụ** (ví dụ không tự tính tổng tiền hay tự duyệt danh sách) - mọi logic nghiệp vụ nằm trong các module tương ứng.

**Tránh lặp code giữa nhập tay và sinh dữ liệu mẫu:** `giaodich` và `ngansach` mỗi module có thêm một hàm công khai `ThemGiaoDichTruc()` / `ThemNganSachTruc()` - nhận một nút đã cấp phát sẵn (đủ dữ liệu) và chỉ làm nhiệm vụ gắn nó vào cuối danh sách. Hàm `ThemGiaoDich()` (Menu 1, nhập tay từ người dùng) và `taodata.cpp` (sinh dữ liệu mẫu) đều gọi chung hàm chèn-cuối này, tránh viết lại logic "duyệt tới cuối danh sách rồi gán con trỏ" ở hai nơi khác nhau.

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
| **[1] Thêm giao dịch** | Nhập ngày, loại (Thu/Chi), danh mục, số tiền, ghi chú. ID tự động sinh bằng cách tìm ID lớn nhất hiện có rồi +1 (duyệt toàn danh sách, trả 0 nếu rỗng) - không bao giờ trùng ID trong một phiên chạy. |
| **[2] Sửa giao dịch** | Hiển thị danh sách, nhập ID, nhấn 1 để giữ nguyên từng trường. |
| **[3] Xóa giao dịch** | Xác nhận bằng ID trước khi xóa. Có xử lý riêng cho trường hợp xóa nút đầu danh sách (cập nhật lại con trỏ đầu) và xóa nút giữa/cuối (nối nút trước với nút sau), sau đó `free()` nút bị xóa. |
| **[4] Xem danh sách** | In toàn bộ giao dịch kèm tổng số bản ghi. |
| **[5] Sắp xếp** | Chọn tăng dần hoặc giảm dần theo số tiền bằng Selection Sort (xem giải thích ở mục dưới). |
| **[6] Thiết lập ngân sách** | Đặt hạn mức chi cho từng danh mục theo tháng/năm. Tự cập nhật nếu (danh mục + tháng + năm) đã tồn tại, nếu chưa thì tạo mới. |
| **[7] Xem ngân sách** | Danh sách hạn mức đã thiết lập. |
| **[8] Báo cáo tổng hợp** | Tổng thu/chi/số dư + biểu đồ ASCII tỷ lệ % chi tiêu theo danh mục + cảnh báo vượt hạn mức. |
| **[9] Dữ liệu mẫu** | Chọn 1 trong 3 kịch bản kiểm thử, xóa dữ liệu cũ trong bộ nhớ và nạp mới. |
| **[0] Lưu và thoát** | Ghi toàn bộ dữ liệu xuống file, giải phóng toàn bộ bộ nhớ đã cấp phát (`GiaiPhongDanhSach`, `GiaiPhongNganSach`), rồi `return 0`. |

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

Biểu đồ ASCII vẽ theo quy ước **mỗi 2% = 1 ký tự `#`**. Chỉ những danh mục có giao dịch loại "Chi" trong tháng được tính; mỗi danh mục chỉ in một lần dù có nhiều giao dịch (nhờ mảng kiểm tra trùng tên trong bộ nhớ tạm).

---

## Định dạng file dữ liệu

Dữ liệu được lưu dưới dạng text thuần, phân tách bằng `|` để tránh lỗi khi nội dung có khoảng trắng (đọc bằng `fgets()` từng dòng, sau đó phân tích bằng `sscanf()`).

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

**Giới hạn độ dài từng trường** (vượt quá sẽ bị cắt khi đọc lại file):

| Trường | Giới hạn ký tự | Hằng số |
|---|---|---|
| `loai` (Thu/Chi) | 4 ký tự | `DO_DAI_LOAI` |
| `danhMuc` | 29 ký tự | `DO_DAI_DANHMUC` |
| `ghiChu` | 99 ký tự | `DO_DAI_GHICHU` |

**Cách chương trình tự bảo vệ khi file bị hỏng:** nếu sửa tay file `.txt` và làm sai định dạng (thiếu cột, sai kiểu dữ liệu...), `sscanf()` sẽ trả về số trường đọc được nhỏ hơn mong đợi - chương trình tự bỏ qua dòng đó mà **không bị crash**. Trường hợp dòng đủ 7 trường nhưng thiếu `ghiChu` (không có dấu `|` cuối), chương trình tự gán `ghiChu` là chuỗi rỗng.

---

## Tại sao dùng danh sách liên kết đơn?

So với mảng tĩnh (`array` khai báo sẵn kích thước), danh sách liên kết đơn (DSLK đơn) cho phép số lượng giao dịch/ngân sách **tăng giảm linh hoạt khi chạy** mà không cần biết trước số lượng tối đa, và không cần dịch chuyển phần tử khi thêm/xóa giữa danh sách. Đánh đổi là **không truy cập được theo chỉ số** - mọi tìm kiếm phải duyệt tuần tự từ đầu (độ phức tạp O(n)).

Mỗi nút `GiaoDich`/`NganSach` được cấp phát bằng `malloc()` và phải `free()` khi không dùng nữa - nếu quên sẽ gây rò rỉ bộ nhớ (memory leak). Chương trình đảm bảo điều này bằng cách gọi `GiaiPhongDanhSach()` và `GiaiPhongNganSach()` **đúng một lần**, ngay trước khi `main` `return 0`.

---

## Vì sao Selection Sort hoán vị dữ liệu, không hoán vị con trỏ?

Trên mảng, đổi chỗ hai phần tử chỉ cần đổi giá trị tại hai chỉ số. Trên danh sách liên kết, việc này phức tạp hơn vì có hai cách:

1. **Đổi con trỏ** - phải tìm và sửa lại các nút *trước* hai nút cần đổi (để chúng trỏ đúng), dễ sai nếu hai nút kề nhau hoặc một trong hai là nút đầu danh sách.
2. **Đổi dữ liệu (data-swap)** - giữ nguyên toàn bộ cấu trúc con trỏ `tiep`, chỉ copy nội dung các trường (`id`, `ngay`, `soTien`, `loai`, `danhMuc`...) giữa hai nút.

Chương trình chọn cách (2) vì đơn giản và an toàn hơn, đổi lại là tốn thêm một lượt copy dữ liệu cho mỗi lần đổi chỗ — không đáng kể với danh sách vài trăm phần tử. Selection Sort luôn chạy O(n²) bất kể dữ liệu đã gần sắp xếp hay chưa, nên thuật toán này phù hợp với quy mô dữ liệu nhỏ như trong bài toán này, không phù hợp nếu số giao dịch lên tới hàng chục nghìn.

---

## Các điểm kỹ thuật nổi bật

| Chủ đề | Cài đặt cụ thể | Vì sao cần |
|---|---|---|
| **DSLK đơn** | `GiaoDich.tiep` và `NganSach.tiep` - thêm cuối, xóa bất kỳ, duyệt tuyến tính | Không biết trước số giao dịch sẽ có, không dùng mảng tĩnh giới hạn kích thước |
| **Selection Sort** | `SapXepTheoSoTien`: 2 vòng for lồng nhau, hoán vị dữ liệu (không đổi con trỏ) | Tránh phải sửa lại liên kết giữa các nút - xem mục phía trên |
| **Lập trình phòng ngừa** | `NhapSoNguyen`, `NhapSoThuc`, `NhapNgay` đều có `while(1)` + kiểm tra biên + `LamSachBoDem()` | Không tin dữ liệu người dùng nhập - chương trình không được crash dù nhập chữ thay số, số âm, ngày không tồn tại |
| **`LamSachBoDem()`** | Đọc và bỏ ký tự thừa còn sót trong `stdin` sau mỗi `scanf()` | Nếu không gọi, ký tự `\n` còn sót sẽ khiến lần `fgets()` kế tiếp đọc ra chuỗi rỗng |
| **Kiểm tra năm nhuận** | `KiemTraNgayHopLe()`: chia hết cho 4 và không chia hết cho 100, hoặc chia hết cho 400 | Đảm bảo ngày như 29/02 chỉ hợp lệ vào đúng năm nhuận |
| **Kiểm tra `malloc()`** | Mọi lần cấp phát đều kiểm tra con trỏ trả về có `NULL` không trước khi dùng | Tránh truy cập vùng nhớ không hợp lệ khi hệ thống hết bộ nhớ |
| **Hàm `static` nội bộ** | `InMotGiaoDich`, `NhapLoai`, `NhapDanhMuc` chỉ dùng trong module, ẩn với module khác | Ngăn các module khác gọi nhầm vào chi tiết cài đặt nội bộ, giảm phụ thuộc chéo |
| **File I/O** | `sscanf` với format `%99[^\n]` đọc được ghi chú có khoảng trắng | Ghi chú có thể chứa dấu cách nên không thể dùng `%s` (dừng ở khoảng trắng) |
| **Không memory leak** | `GiaiPhongDanhSach` + `GiaiPhongNganSach` được gọi trong `main` trước khi `return 0` | Trả lại toàn bộ vùng nhớ đã `malloc()` trong suốt phiên chạy |

---

## Đã kiểm thử những gì?

Báo cáo ghi lại các trường hợp đã kiểm thử thủ công, tất cả đều đạt kết quả mong đợi:

- **Nhập liệu:** số âm, số 0, nhập chữ thay số, ngày không tồn tại (30/02), năm nhuận (29/02/2024 hợp lệ, 29/02/2025 không hợp lệ), loại sai/đúng, danh mục rỗng.
- **CRUD giao dịch:** thêm vào danh sách rỗng, thêm nhiều lần (ID tự tăng đúng), sửa ID hợp lệ/không tồn tại, xóa nút đầu/giữa/cuối, xóa ID không tồn tại.
- **Sắp xếp:** tăng dần và giảm dần trên cùng một bộ dữ liệu mẫu.
- **File I/O:** chạy lần đầu chưa có file, ghi rồi đọc lại đúng dữ liệu, dòng lỗi định dạng bị bỏ qua không crash, ghi chú có khoảng trắng đọc lại không bị cắt, ghi chú rỗng.
- **Bộ nhớ:** xóa hết rồi thêm lại ID vẫn tăng đúng, thoát chương trình không rò rỉ bộ nhớ.

---

## Lưu ý quan trọng

- **Dữ liệu chỉ lưu khi chọn [0] Lưu và thoát** - tắt cửa sổ đột ngột sẽ mất thay đổi vì dữ liệu đang ở trong bộ nhớ (DSLK), chưa được ghi xuống file.
- **Lần đầu chạy** khi chưa có file: chương trình tự bắt đầu với danh sách rỗng, không báo lỗi.
- **Xóa toàn bộ dữ liệu:** xóa nội dung hai file trong thư mục `data/` hoặc chọn kịch bản mới ở Menu 9.
- **Mã ID giao dịch** được sinh tự động bằng `IDLonNhat + 1`, không bao giờ trùng trong một phiên.
- **Không chạy hai instance** chương trình cùng lúc trên cùng thư mục - cả hai sẽ cùng ghi đè lên `data/giaodich.txt` và `data/ngansach.txt` khi thoát, gây mất dữ liệu của bên thoát trước.
