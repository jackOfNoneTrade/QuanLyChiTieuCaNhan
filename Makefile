CXX      = g++
CXXFLAGS = -Wall -Wextra -I include/
SRCS     = src/main.cpp src/tienich.cpp src/giaodich.cpp \
           src/ngansach.cpp src/baocao.cpp src/taodata.cpp
TARGET   = build/quanlychitieu.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Bien dich thanh cong -> $(TARGET)"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	@echo "[OK] Da xoa file bien dich."
