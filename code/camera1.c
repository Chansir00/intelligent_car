#include "zf_common_headfile.h"


struct LEFT_EDGE L_edge[140];
struct RIGHT_EDGE R_edge[140];
uint8_t Image_use_zip[IMAGE_H][IMAGE_W];
uint8_t Image_use_out[IMAGE_H][IMAGE_W];
uint8_t L_edge_count=0, R_edge_count = 0;                     //���ұߵ�ĸ���
uint8_t dire_left,dire_right;                                 //��¼��һ��������λ��
uint8_t L_search_amount = 140, R_search_amount = 140;  //���ұ߽��ѵ�ʱ��������ĵ�
uint16_t L_corner_flag = 0;//��յ���ڱ�־
const uint16_t Boundary_search_end = 10; // Define Boundary_search_end with an appropriate value
uint16_t L_corner_row = 0;//��յ�������
uint16_t L_corner_col = 0;//��յ�������
uint16_t L_corner_angle = 0;//��յ�Ƕ�
uint16_t R_corner_flag = 0;//�ҹյ���ڱ�־
uint16_t R_corner_row = 0;//�ҹյ�������
uint16_t R_corner_col = 0;//�ҹյ�������
uint16_t R_corner_angle = 0;//�ҹյ�Ƕ�
uint16_t enable_L_corner=1,enable_R_corner=1;
uint8_t left_findflag = 0; // ����ҵ���־
uint8_t right_findflag = 0; // �ұ��ҵ���־
uint16_t left_lose = 0; // ��ʼ����߶�ʧ��־
uint16_t right_lose = 0; // ��ʼ���ұ߶�ʧ��־
uint16_t L_start_x = 0; // ��ʼ����߽���ʼ��x����
uint16_t L_start_y = 0; // ��ʼ����߽���ʼ��y����
uint16_t R_start_x = 0; // ��ʼ���ұ߽���ʼ��x����
uint16_t R_start_y = 0; // ��ʼ���ұ߽���ʼ��y����

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ٴ��
//  @return     uint8
//  @since      v1.1
//  Sample usage:   OTSU_Threshold = otsuThreshold(mt9v03x_image_dvp[0]);//�����ֵ
//-------------------------------------------------------------------------------------------------------------------
uint8_t otsuThreshold(uint8_t *image)   //ע�������ֵ��һ��Ҫ��ԭͼ��
{

    int Pixel_Max=0;
    int Pixel_Min=255;
    uint16_t width = MT9V03X_W;
    uint16_t height = MT9V03X_H;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height/4;
    uint8_t threshold = 0;
    uint8_t last_threshold = 0;
    uint8_t* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32_t gray_sum=0;
    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
            if(data[i * width + j]>Pixel_Max)   Pixel_Max=data[i * width + j];
            if(data[i * width + j]<Pixel_Min)   Pixel_Min=data[i * width + j];
        }
    }

    //����ÿ������ֵ�ĵ�������ͼ���еı���

    for (i = Pixel_Min; i < Pixel_Max; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;

    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = Pixel_Min; j < Pixel_Max; j++)
    {

        w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
        u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ

        w1=1-w0;
        u1tmp=gray_sum/pixelSum-u0tmp;

        u0 = u0tmp / w0;              //����ƽ���Ҷ�
        u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
        u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
        deltaTmp = (float)(w0 *w1* (u0 - u1)* (u0 - u1)) ;
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = j;
        }
        if (deltaTmp < deltaMax)
        {
            break;
        }

    }

    if(threshold>90 && threshold<130)
        last_threshold = threshold;
    else
        threshold = last_threshold;

    return threshold;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͼ��ѹ��
//  @return     void
//  @since      v2.0
//  Sample usage:   void compressimage();
//-------------------------------------------------------------------------------------------------------------------

void compressimage(void)
{
  int i, j, row, line;
  const float div_h = MT9V03X_H / IMAGE_H, div_w = MT9V03X_W / IMAGE_W; // Replace 50.0 with the appropriate value for MINGW_DDK_H
  for (i = 0; i < IMAGE_H; i++)
  {
    row = i * div_h + 0.5;
    for (j = 0; j < IMAGE_W; j++)
    {
      line = j * div_w + 0.5;
      Image_use_zip[i][j] = mt9v03x_image[row][line];
    }
  }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Soble�̶���ֵ
//  @return     void
//  @since      v1.2
//  Sample usage:   sobel(Image_use_zip_zip, Image_use_zip, 60);
//-------------------------------------------------------------------------------------------------------------------
void sobel (uint8_t imageIn[IMAGE_H][IMAGE_W], uint8_t imageOut[IMAGE_H][IMAGE_W], uint8_t Threshold)
{
    /** �����˴�С */
    short KERNEL_SIZE = 3;
    short xStart = KERNEL_SIZE / 2;
    short xEnd = IMAGE_W - KERNEL_SIZE / 2;
    short yStart = KERNEL_SIZE / 2;
    short yEnd = IMAGE_H - KERNEL_SIZE / 2;
    short i, j;
    short temp[2];
    for (i = yStart; i < yEnd; i++)
    {
        for (j = xStart; j < xEnd; j++)
        {
            /* ���㲻ͬ�����ݶȷ�ֵ  */
            temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
            - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]                      // {-1, 0, 1},
            - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];             // {-1, 0, 1}};

            temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
            - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]                      // { 0,  0,  0},
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];             // { 1,  1,  1}};

            temp[0] = abs(temp[0]);
            temp[1] = abs(temp[1]);

            /* �ҳ��ݶȷ�ֵ���ֵ  */
            if (temp[0] < temp[1])
                temp[0] = temp[1];

            if (temp[0] > Threshold) imageOut[i][j] = 0;
            else    imageOut[i][j] = 255;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ͼ�񻭺ڿ�Ϊ��������׼��
//  @return     void
//  @since      v1.0
//  Sample usage:   image_draw_rectan(Image_use_zip);
//-------------------------------------------------------------------------------------------------------------------
void image_draw_rectan(uint8_t image[IMAGE_H][IMAGE_W])
{
    uint8_t i = 0;
    for (i = 0; i < IMAGE_H; i++)
    {
        image[i][0] = 0;
        image[i][1] = 0;
        image[i][IMAGE_W - 1] = 0;
        image[i][IMAGE_W - 2] = 0;
    }
    for (i = 0; i < IMAGE_W; i++)
    {
        image[0][i] = 0;
        image[1][i] = 0;
    }
}


/*---------------------------------------------------------------
 ����    ����search_neighborhood
 ����    �ܡ��������ұ߽�
 ����    ������
 ���� �� ֵ����
 ��ע�����
 ----------------------------------------------------------------*/


void search_neighborhood(void)
{
    L_edge_count = 0;//��ߵ������0
    R_edge_count = 0;//�ұߵ������0

    if(left_findflag)//�����߽����ڲ��ҵ�,��ʼ����
    {
        //��������
        L_edge[0].row = L_start_y;
        L_edge[0].col = L_start_x;
        L_edge[0].flag = 1;
        uint16_t curr_row = L_start_y;//��ʼ��������
        uint16_t curr_col = L_start_x;//��ʼ��������
        dire_left = 0; //��ʼ���ϸ��߽�������
        //��ʼ���ߣ����ȡ150���㣬���������ѣ���7����λ
        for(int i = 1;i < L_search_amount; i++)    //�������150����
        {
            ////Խ���˳� ��Խ�����Խ�磨���������������ң�
            if(curr_row+1 < Boundary_search_end || curr_row>IMAGE_H-1)  break;
            //���߹���
            if(dire_left != 2&&Image_use_out[curr_row-1][curr_col-1]==0 &&Image_use_out[curr_row-1][curr_col]==1)   //���Ϻڣ�2���ұ߰�
            {
                curr_row = curr_row -1;
                curr_col = curr_col -1;
                L_edge_count = L_edge_count +1;
                dire_left = 7;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else if(dire_left!=3&&Image_use_out[curr_row-1][curr_col+1]==0&&Image_use_out[curr_row][curr_col+1]==1)    //���Ϻڣ�3���±߰�
            {
                curr_row = curr_row -1;
                curr_col = curr_col + 1;
                L_edge_count = L_edge_count + 1;
                dire_left = 6;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else if(Image_use_out[curr_row-1][curr_col]==0&&Image_use_out[curr_row-1][curr_col+1]==1)                  //���Ϻڣ�1���Ұ�
            {
                curr_row = curr_row - 1;
                L_edge_count = L_edge_count + 1;
                dire_left = 0;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else if(dire_left!=5&&Image_use_out[curr_row][curr_col-1]==0&&Image_use_out[curr_row-1][curr_col-1]==1)     //����ڣ�5���ϰ�
            {
                curr_col = curr_col - 1;
                L_edge_count = L_edge_count +1;
                dire_left = 4;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else if(dire_left!=4&&Image_use_out[curr_row][curr_col+1]==0&&Image_use_out[curr_row+1][curr_col+1]==1)  //���Һڣ�4���°�
            {
                curr_col = curr_col + 1;
                L_edge_count = L_edge_count +1;
                dire_left = 5;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else if(dire_left!=6&&Image_use_out[curr_row+1][curr_col-1]==0&&Image_use_out[curr_row][curr_col-1]==1)    //���ºڣ�6���ϰ�
            {
                curr_row = curr_row + 1;
                curr_col = curr_col -1;
                L_edge_count = L_edge_count +1;
                dire_left = 3;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else if(dire_left!=7&&Image_use_out[curr_row+1][curr_col+1]==0&&Image_use_out[curr_row+1][curr_col]==1)    //���ºڣ�7�����
            {
                curr_row = curr_row + 1;
                curr_col = curr_col + 1;
                L_edge_count = L_edge_count +1;
                dire_left = 2;
                L_edge[i].row = curr_row;
                L_edge[i].col = curr_col;
                L_edge[i].flag = 1;
            }
            else
                break;
        }
    }

    if(right_findflag)//����ұ߽���ڲ��ѵ�
             {
                 R_edge[0].row = R_start_y;
                 R_edge[0].col = R_start_x;
                 R_edge[0].flag = 1;
                 uint16_t curr_row = R_start_y;
                 uint16_t curr_col = R_start_x;
                 dire_right = 0;
                 for(int i = 1;i<R_search_amount;i++)
                 {
		////Խ���˳� ��Խ�����Խ�磨���������������ң�
                     if(curr_row < Boundary_search_end || curr_row>IMAGE_H-1||curr_row+1<Boundary_search_end)  break;
                     //���߹���
                     if(curr_col<IMAGE_W&&dire_right!=3&&Image_use_zip[curr_row-1][curr_col+1]==0&&Image_use_zip[curr_row-1][curr_col]==1)    //���Ϻڣ�3�����
                     {
                         curr_row = curr_row - 1;
                         curr_col = curr_col + 1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 6;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }
                     else if(dire_right!=2&&Image_use_zip[curr_row-1][curr_col-1]==0&&Image_use_zip[curr_row][curr_col-1]==1) //���Ϻڣ�2���°�
                     {
                         curr_row = curr_row-1;
                         curr_col = curr_col-1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 7;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }
                     else if(Image_use_zip[curr_row-1][curr_col]==0&&Image_use_zip[curr_row-1][curr_col-1]==1)                  //���Ϻڣ�1�����
                     {
                         curr_row = curr_row - 1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 0;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }
                     else if(dire_right!=4&&Image_use_zip[curr_row][curr_col+1]==0&&Image_use_zip[curr_row-1][curr_col+1]==1)   //���Һڣ�4���ϰ�
                     {
                         curr_col = curr_col + 1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 5;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }
                     else if(dire_right!=5&&Image_use_zip[curr_row][curr_col-1]==0&&Image_use_zip[curr_row+1][curr_col-1]==1)   //����ڣ�5���°�
                     {
                         curr_col = curr_col-1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 4;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }


                     else if(dire_right!=6&&Image_use_zip[curr_row+1][curr_col-1]==0&&Image_use_zip[curr_row+1][curr_col]==1)   //���ºڣ�6���Ұ�
                     {
                         curr_row = curr_row + 1;
                         curr_col = curr_col - 1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 3;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }
                     else if(dire_right!=7&&Image_use_zip[curr_row+1][curr_col+1]==0&&Image_use_zip[curr_row][curr_col+1]==1)   //���ºڣ�7���ϰ�
                     {
                         curr_row = curr_row + 1;
                         curr_col = curr_col + 1;
                         R_edge_count = R_edge_count + 1;
                         dire_right = 2;
                         R_edge[i].row = curr_row;
                         R_edge[i].col = curr_col;
                         R_edge[i].flag = 1;
                     }
                     else
                         break;
                 }
             }
}

/*---------------------------------------------------------------
 ����    ����clear_find_point
 ����    �ܡ�������߽��ʼ��
 ����    ������
 ���� �� ֵ��
 ��ע�����
 ----------------------------------------------------------------*/
void clear_find_point(void)
{
    for(int i = 0;i<L_edge_count;i++)
    {
        L_edge[i].row = 0;
        L_edge[i].col = 0;
        L_edge[i].flag = 0;
    }
    for(int i = 0;i<R_edge_count;i++)
    {
        R_edge[i].row = 0;
        R_edge[i].col = 0;
        R_edge[i].flag = 0;
    }
}
/*---------------------------------------------------------------
 ����    ����calc_diff
 ����    �ܡ���Ⱥ�
 ����    ������
 ���� �� ֵ��
 ��ע�����Լ�Ŵ�128��
 ----------------------------------------------------------------*/
uint16_t calc_diff(uint16_t x, uint16_t y)
{
    return ( ((x-y)<<7)/(x+y) );
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �޷�
//  @param      x               ���޷�������
//  @param      y               �޷���Χ(���ݻᱻ������-y��+y֮��)
//  @return     float           �޷�֮�������
//  Sample usage:               float dat = limit(500,300);//���ݱ�������-300��+300֮��  ��˷��صĽ����300
//-------------------------------------------------------------------------------------------------------------------
float limit(float x, uint32_t y)
{
    if(x>y)             return (float)y;
    else if(x<-y)       return (float)(-y);
    else                return x;
}

/*---------------------------------------------------------------
 ����    ����get_turning_point
 ����    �ܡ��յ���
 ����    ������
 ���� �� ֵ��
 ��ע�����
 ----------------------------------------------------------------*/

void get_turning_point(void)
{
    L_corner_flag = 0;// ��ʼ������
    L_corner_row = 0;
    L_corner_col = 0;
    L_corner_angle = 0;
    if(enable_L_corner) //���ʹ��������յ�
    {
        if(L_edge_count > 9&&L_start_y>=IMAGE_H/2&&left_lose<=IMAGE_H/2)
        {
            for(int i = 0; i<L_edge_count-9;i++)
            {
                if(L_edge[i+8].row>5)
                {
                    if((L_edge[i].col - L_edge[i + 4].col) * (L_edge[i + 8].col - L_edge[i + 4].col) +
                       (L_edge[i].row - L_edge[i + 4].row) * (L_edge[i + 8].row - L_edge[i + 4].row) >= 0) //����ȷ��Ϊ��ǻ���ֱ�� ������
                    {
                        L_corner_angle = Get_angle(L_edge[i].col, L_edge[i].row, L_edge[i + 4].col, L_edge[i + 4].row, L_edge[i + 8].col, L_edge[i + 8].row); //��Ƕ�
                        if(L_edge[i+4].col>L_edge[i+8].col&&L_corner_angle>=28&&L_corner_angle<=110)
                        {
                            L_corner_flag = 1;
                            L_corner_row = L_edge[i+4].row;
                            L_corner_col = L_edge[i+4].col;
                            break;
                        }
                    }
                }
            }
        }
    }
    R_corner_flag = 0;//��ʼ������
    R_corner_row = 0;
    R_corner_col = 0;
    R_corner_angle = 0;
    if(enable_R_corner)    //���ʹ�������ҹյ�
    {
        if(R_edge_count > 9&&R_start_y>=IMAGE_H/2&&right_lose<=IMAGE_H/2)
        {
            for(int i = 0; i<R_edge_count-9;i++)
            {
                if(R_edge[i+8].row>5)
                {
                    if((R_edge[i].col - R_edge[i + 4].col) * (R_edge[i + 8].col - R_edge[i + 4].col) +
                    (R_edge[i].row - R_edge[i + 4].row) * (R_edge[i + 8].row - R_edge[i + 4].row) >= 0) //����ȷ��Ϊ��ǻ���ֱ�� ������
                    {
                        R_corner_angle = Get_angle(R_edge[i].col, R_edge[i].row, R_edge[i + 4].col, R_edge[i + 4].row, R_edge[i + 8].col, R_edge[i + 8].row); //��Ƕ�
                        if(R_edge[i+8].col>R_edge[i+4].col&&R_corner_angle>=28&&R_corner_angle<=110)
                        {
                            R_corner_flag = 1;
                            R_corner_row = R_edge[i+4].row;
                            R_corner_col = R_edge[i+4].col;
                            break;
                        }
                    }
                }
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��͸��֪�������γɵĽǶ�(�����Ͻ�Ϊԭ���γ�����ϵ)
//  @param      Ax��Ay      �±ߵ�
//  @param      Bx��By      Ҫ��Ƕȵ�һ��
//  @param      Cx��Cy      �ϱߵ�
//  @return
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
float hd[3][3] ={{-0.436025, 0.000000, 21.365217}, {0.424457, 0.487500, -22.048370}, {0.018944, -0.000000, 0.071739}};
//x=[18,18,69,69]  % ����ΪA��B��D��C������ͷ��ȡ����Ƭ�еĵ�������
//y=[70,121,70,121] % ����ΪA��B��D��C������ͷ��ȡ����Ƭ�еĵĺ�����
float Get_angle(float Ax, float Ay, float Bx, float By, float Cx, float Cy)
{

    float BA = 0.00;//����BA��ģ
    float BC = 0.00;
    float SBA_BC = 0.00;//������˵�ֵ
    float angle = 0.00;

    float AX=((hd[0][0] * Ax + hd[0][1] * Ay + hd[0][2])/(hd[2][0] * Ax + hd[2][1] * Ay + hd[2][2]));
    float AY=((hd[1][0] * Ax + hd[1][1] * Ay + hd[1][2])/(hd[2][0] * Ax + hd[2][1] * Ay + hd[2][2]));
    float BX=((hd[0][0] * Bx + hd[0][1] * By + hd[0][2])/(hd[2][0] * Bx + hd[2][1] * By + hd[2][2]));
    float BY=((hd[1][0] * Bx + hd[1][1] * By + hd[1][2])/(hd[2][0] * Bx + hd[2][1] * By + hd[2][2]));
    float CX=((hd[0][0] * Cx + hd[0][1] * Cy + hd[0][2])/(hd[2][0] * Cx + hd[2][1] * Cy + hd[2][2]));
    float CY=((hd[1][0] * Cx + hd[1][1] * Cy + hd[1][2])/(hd[2][0] * Cx + hd[2][1] * Cy + hd[2][2]));

    BA = sqrt((AX-BX)*(AX-BX)+(AY-BY)*(AY-BY));
    BC = sqrt((CX-BX)*(CX-BX)+(CY-BY)*(CY-BY));

    SBA_BC = (AX-BX)*(CX-BX)+(AY-BY)*(CY-BY);

    angle =  acos(SBA_BC*1.00/(BA*BC));

    return angle*57.3;
}


uint8_t Deal_img(void) {
    //compressimage();                                   // ͼ��ѹ��
    uint8_t threshold = otsuThreshold(mt9v03x_image[0]);  // ������ֵ
    sobel(mt9v03x_image[0], Image_use_out[0], threshold); // ��Ե���
    image_draw_rectan(Image_use_out[0]);               // ���Ӻڿ�
    search_neighborhood();                             // ���ұ߽�
    clear_find_point();                                // ����߽��
    get_turning_point();                               // ��ȡ�յ�

    // ����ǶȲ��޷�
    float angle = Get_angle(L_corner_row, L_corner_col, R_corner_row, R_corner_col, IMAGE_H, IMAGE_W);
    float limited_angle = limit(angle, 30);
    
    return limited_angle;
}

void adjust_motor_speed() {
    float angle = Deal_img(); // ��ȡƫ�ƽǶ�
    
    // �����ٶȺ͵�������
    int base_speed = 3000;
    int adjust_value = angle * 50; // ���ݽǶȵ���
    
    Set_Left_Motor_Duty(limit(base_speed + adjust_value, MOTOR_A_DUTY));
    Set_Right_Motor_Duty(limit(base_speed - adjust_value, MOTOR_B_DUTY));
}




int calculate_offset(void) {
    int left_col = 0, right_col = 0;
    if (L_edge_count > 0) left_col = L_edge[L_edge_count / 2].col;
    if (R_edge_count > 0) right_col = R_edge[R_edge_count / 2].col;

    int track_center = (left_col + right_col) / 2;
    int image_center = IMAGE_W / 2;
    return track_center - image_center; // ƫ����
}