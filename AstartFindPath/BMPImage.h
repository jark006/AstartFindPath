#pragma once

#include <string>
#include <stdexcept>

#ifndef NDEBUG
#include <typeinfo>
#include <cstring>

#endif

/** ------------------���������ض���------------------------ */
typedef int int4;              // 4 bytes
typedef unsigned int uint;     // 4 bytes
typedef unsigned char uchar;   // 1 byte
typedef unsigned int uint4;   // 4 bytes
typedef unsigned short uint2;  // 2 bytes
/** -------------------------------------------------------- */

/** ------------------��ɫ�ṹ���ض���---------------------- */
// Color Palette�Ľṹ�壬Ҳ��RGBA��ɫ�ṹ��
typedef struct {
	uchar b;
	uchar g;
	uchar r;
	uchar a;
}BGRA, ColorPalette;

// RGB��ɫ�ṹ��
typedef struct {
	uchar b;
	uchar g;
	uchar r;
}BGR;
/** -------------------------------------------------------- */

class BMPImage {
private:
	/** -------------BMP�ļ�ͷ��BMP��Ϣͷ���ݽṹ����----------- */
	//�ο���������
		//https://blog.csdn.net/u012877472/article/details/50272771
		//https://blog.csdn.net/lanbing510/article/details/8176231
		//bmp�ļ�ͷ��bmp file header������14�ֽڣ�
	typedef struct {
		uint2 bfType;           //2�ֽڣ��ļ����ͣ���Ӧ��0x4d42('BM')
		uint4 bfSize;           //4�ֽڣ��ļ���С���ֽ�Ϊ��λ��
		uint2 bfReserved1;      //2�ֽڣ���������������Ϊ0
		uint2 bfReserved2;      //2�ֽڣ���������������Ϊ0
		uint4 bfOffBits;        //4�ֽڵ�ƫ�ƣ���ʾ���ļ�ͷ��λͼ���ݵ�ƫ��
	} BMPFileHeader;

	//λͼ��Ϣͷ��bitmap information������40�ֽڣ�
	typedef struct {
		uint4 biSize;           //4�ֽڣ���Ϣͷ�Ĵ�С����40��
		int4 biWidth;           //4�ֽڣ�������Ϊ��λ˵��ͼ��Ŀ�ȣ�
		int4 biHeight;          //4�ֽڣ�������Ϊ��λ˵��ͼ��ĸ߶ȣ����Ϊ����˵��λͼ����
		uint2 biPlanes;         //2�ֽڣ�ΪĿ���豸˵����ɫƽ�������ܱ�����Ϊ1��
		uint2 biBitCount;       //2�ֽڣ�˵��������/��������ֵ��1��2��4��8��16��24��32��
		uint4 biCompression;    //4�ֽڣ�˵��ͼ���ѹ�����ͣ�0(BI_RGB)��ʾ��ѹ����
		uint4 biSizeImage;      //4�ֽڣ�˵��λͼ���ݵĴ�С.
		int4 biXPelsPerMeter;   //4�ֽڣ���ʾˮƽ�ֱ��ʣ���λ������/�ף�
		int4 biYPelsPerMeter;   //4�ֽڣ���ʾ��ֱ�ֱ��ʣ���λ������/�ף�
		uint4 biClrUsed;        //4�ֽڣ�λͼʹ�õĵ�ɫ���е���ɫ��������Ϊ0˵��ʹ�����У�
		uint4 biClrImportant;   //4�ֽڣ���ͼ����ʾ����ҪӰ�����ɫ��������Ϊ0˵������Ҫ��
	} BMPInfoHeader;
	/** -------------------------------------------------------- */

	/** ---------------------���к�����------------------------- */
public:
	/**
	 * ���캯������ʼ��һ���յ�BMPImage
	 */
	explicit BMPImage();
	/**
	 * ���캯��������һ��BMPͼ��,��ʧ��ʱ���׳��쳣
	 * @param bmp_file_path ͼ��·��
	 */
	explicit BMPImage(const char* bmp_file_path);
	/**
	 * ���캯����������СΪwidth*height��24λ�ĺ�ɫͼ��
	 * ����ʧ��ʱ���׳��쳣��
	 * @param width ���
	 * @param height �߶�
	 * @param depth ��ȣ�Ŀǰ��֧��24λ��32λͼ��
	 */
	explicit BMPImage(int4 width, int4 height, uint2 depth = 24);
	/**
	 * �������캯��
	 * @param image ͼ��
	 */
	BMPImage(const BMPImage &image);
	/**
	 * ��ֵ���캯��
	 * @param image �Ⱥ��ұߵ�ͼ
	 * @return ���ظ��Ƶ�ͼ
	 */
	BMPImage &operator=(const BMPImage &image);
	/**
	 * ��������
	 */
	virtual ~BMPImage();
	/**
	  * ������СΪwidth*height��24λ�ĺ�ɫͼ��
	  * @param width ���
	  * @param height �߶�
	  * @param depth ��ȣ�Ŀǰ��֧��24λͼ��
	  * @return �ɹ�����true������false
	  */
	bool create(int4 width, int4 height, uint2 depth = 24);
	/**
	 * ����һ��BMPͼ��
	 * @param bmp_file_path ͼ��·��
	 * @return �ɹ�����true������false
	 */
	bool open(const char* bmp_file_path);
	/**
	 * ����BMPͼ��
	 * @param save_path ����·��
	 * @return �ɹ�����true������false
	 */
	bool save(const char* save_path);
	/**
	 * ����(row,col)������ֵ������
	 * @tparam T ��ȡ��ֵ�ֱ�Ϊuchar(8λ����ͨ��ͼ��)��
	 * BGR(24λ��3ͨ��ͼ��)��BGRA(32λ����ͨ��ͼ��)
	 * @param row ��
	 * @param col ��
	 * @return T���͵�����
	 */
	template <typename T>
	T & at(uint row, uint col);
	/**
	 * ���ͼ��
	 * @return �ɹ�����true������false
	 */
	bool clear();

	/**
	 * ����ͼ����
	 * @return ���
	 */
	int4 width();
	/**
	 * ����ͼ��߶�
	 * @return  �߶�
	 */
	int4 height();
	/**
	 * ����ͼ�����
	 * @return ���
	 */
	uint2 depth();
	/** -------------------------------------------------------- */

	/** ----------------------˽�б�����------------------------ */
private:
	int4 m_width;       //ͼ����
	int4 m_height;      //ͼ�����
	uint2 m_depth;      //ͼ�����
	uint4 m_row_size;   //ÿ���ֽ���
	uchar *m_data;      //ͼ�����ݴ洢��

	BMPFileHeader m_file_header;    //BMPͼ����ļ�ͷ
	BMPInfoHeader m_info_header;    //BMPͼ�����Ϣͷ
	uint m_color_palette_size;      //BMP�ĵ�ɫ�������С
	ColorPalette *m_color_palette;  //��ɫ��(Color Palette),��ѡ��
/** -------------------------------------------------------- */

/** ------------------------˽�к�����------------------------ */
	/**
	 * ����Ƿ�Խ��,�Լ�����Ƿ�ƥ��
	 * @param row ��
	 * @param col ��
	 * @param depth ���
	 * @return Խ���ӡ������Ϣ������false
	 */
	bool valid(int4 row, int4 col, uint2 depth);
	/** -------------------------------------------------------- */
};

// ģ�庯����ʵ��Ҫ����ͷ�ļ���
template<typename T>
T &BMPImage::at(uint row, uint col) {
	size_t elem_size = sizeof(T);
#ifdef DEBUG //����DEBUGʱ���
	if (!valid(row, col, (uint2)(elem_size * 8))) {
		throw std::runtime_error("Index is overflow or T is not match depth");
	}
#endif
	T *value = nullptr;
	// ��������
	size_t index = 0;
	if (m_height > 0) {
		// ͼ�����ݵĴ洢˳���Ǵ����µ����ϣ�ͼƬ�ϵĵ�һ�д���m_data�����һ����
		index = (m_height - row - 1) * m_row_size + col * elem_size;
	}
	else {
		// ͼ�����ݵĴ洢˳���Ǵ����µ����ϣ�ͼƬ�ϵĵ�һ�д���m_data�ĵ�һ����
		index = row * m_row_size + col * elem_size;
	}
	value = (T*)(m_data + index);
	return *value;
}



