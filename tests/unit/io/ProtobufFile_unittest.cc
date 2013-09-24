#include <shogun/lib/SGVector.h>
#include <shogun/lib/SGMatrix.h>
#include <shogun/mathematics/Random.h>

#include <cstdio>

#include <unistd.h>
#include <gtest/gtest.h>

using namespace shogun;

#ifdef HAVE_PROTOBUF
#include <shogun/io/ProtobufFile.h>

TEST(ProtobufFileTest, vector_int32)
{
	CRandom* rand=new CRandom();

	int32_t len=1024*1024;
	SGVector<int32_t> data(len);
	for (int32_t i=0; i<len; i++)
		data[i]=(int32_t) rand->random(0, len);

	CProtobufFile* fin;
	CProtobufFile* fout;

	fout=new CProtobufFile("ProtobufFileTest_int32_output.txt",'w', NULL);
	fout->set_vector(data.vector, len);
	SG_UNREF(fout);

	SGVector<int32_t> data_from_file(true);
	fin=new CProtobufFile("ProtobufFileTest_int32_output.txt",'r', NULL);
	fin->get_vector(data_from_file.vector, data_from_file.vlen);
	EXPECT_EQ(data_from_file.vlen, len);

	for (int32_t i=0; i<data_from_file.vlen; i++)
	{
		EXPECT_EQ(data_from_file[i], data[i]);
	}
	SG_UNREF(fin);
	SG_UNREF(rand);
	unlink("ProtobufFileTest_int32_output.txt");
}

TEST(ProtobufFileTest, vector_float64)
{
	CRandom* rand=new CRandom();

	int32_t len=1024*1024;
	SGVector<float64_t> data(len);
	for (int32_t i=0; i<len; i++)
		data[i]=(float64_t) rand->random(0, 1);

	CProtobufFile* fin;
	CProtobufFile* fout;

	fout=new CProtobufFile("ProtobufFileTest_float64_output.txt",'w', NULL);
	fout->set_vector(data.vector, len);
	SG_UNREF(fout);

	SGVector<float64_t> data_from_file(true);
	fin=new CProtobufFile("ProtobufFileTest_float64_output.txt",'r', NULL);
	fin->get_vector(data_from_file.vector, data_from_file.vlen);
	EXPECT_EQ(data_from_file.vlen, len);

	for (int32_t i=0; i<data_from_file.vlen; i++)
	{
		EXPECT_NEAR(data_from_file[i], data[i], 1E-14);
	}
	SG_UNREF(fin);
	SG_UNREF(rand);
	unlink("ProtobufFileTest_float64_output.txt");
}

TEST(ProtobufFileTest, matrix_int32)
{
	CRandom* rand=new CRandom();

	int32_t num_rows=1024;
	int32_t num_cols=512;
	SGMatrix<int32_t> data(num_rows, num_cols);
	for (int32_t i=0; i<num_rows; i++)
	{
		for (int32_t j=0; j<num_cols; j++)
			data(i, j)=(int32_t) rand->random(0, num_rows);
	}

	CProtobufFile* fin;
	CProtobufFile* fout;

	fout=new CProtobufFile("ProtobufFileTest_int32_output.txt",'w', NULL);
	fout->set_matrix(data.matrix, num_cols, num_rows);
	SG_UNREF(fout);

	SGMatrix<int32_t> data_from_file(true);
	fin=new CProtobufFile("ProtobufFileTest_int32_output.txt",'r', NULL);
	fin->get_matrix(data_from_file.matrix, data_from_file.num_cols, data_from_file.num_rows);
	EXPECT_EQ(data_from_file.num_rows, num_rows);
	EXPECT_EQ(data_from_file.num_cols, num_cols);

	for (int32_t i=0; i<num_rows; i++)
	{
		for (int32_t j=0; j<num_cols; j++)
			EXPECT_EQ(data_from_file(i, j), data(i, j));
	}

	SG_UNREF(fin);
	SG_UNREF(rand);
	unlink("ProtobufFileTest_int32_output.txt");
}

TEST(ProtobufFileTest, matrix_float64)
{
	CRandom* rand=new CRandom();

	int32_t num_rows=1024;
	int32_t num_cols=512;
	SGMatrix<float64_t> data(num_rows, num_cols);
	for (int32_t i=0; i<num_rows; i++)
	{
		for (int32_t j=0; j<num_cols; j++)
			data(i, j)=(float64_t) rand->random(0, 1);
	}

	CProtobufFile* fin;
	CProtobufFile* fout;

	fout=new CProtobufFile("ProtobufFileTest_int32_output.txt",'w', NULL);
	fout->set_matrix(data.matrix, num_cols, num_rows);
	SG_UNREF(fout);

	SGMatrix<float64_t> data_from_file(true);
	fin=new CProtobufFile("ProtobufFileTest_int32_output.txt",'r', NULL);
	fin->get_matrix(data_from_file.matrix, data_from_file.num_cols, data_from_file.num_rows);
	EXPECT_EQ(data_from_file.num_rows, num_rows);
	EXPECT_EQ(data_from_file.num_cols, num_cols);

	for (int32_t i=0; i<num_rows; i++)
	{
		for (int32_t j=0; j<num_cols; j++)
			EXPECT_NEAR(data_from_file(i, j), data(i, j), 1E-14);
	}

	SG_UNREF(fin);
	SG_UNREF(rand);
	unlink("ProtobufFileTest_float64_output.txt");
}

TEST(ProtobufFileTest, string_list_char)
{
	CRandom* rand=new CRandom();

	int32_t num_str=1024;
	int32_t max_string_len=1024;
	SGString<char>* strings=SG_MALLOC(SGString<char>, num_str);
	for (int32_t i=0; i<num_str; i++)
	{
	 	strings[i]=SGString<char>((int32_t) rand->random(1, max_string_len));
	 	for (int32_t j=0; j<strings[i].slen; j++)
	 		strings[i].string[j]=(char) rand->random(0, 255);
	}

	CProtobufFile* fin;
	CProtobufFile* fout;

	fout=new CProtobufFile("ProtobufFileTest_char_output.txt",'w', NULL);
	fout->set_string_list(strings, num_str);
	SG_UNREF(fout);

	SGString<char>* data_from_file=NULL;
	int32_t num_str_from_file=0;
	int32_t max_string_len_from_file=0;
	fin=new CProtobufFile("ProtobufFileTest_char_output.txt",'r', NULL);
	fin->get_string_list(data_from_file, num_str_from_file, max_string_len_from_file);
	EXPECT_EQ(num_str_from_file, num_str);

	for (int32_t i=0; i<num_str; i++)
	{
	 	for (int32_t j=0; j<strings[i].slen; j++)
	 		EXPECT_EQ(strings[i].string[j], data_from_file[i].string[j]);
	}

	SG_UNREF(fin);
	SG_UNREF(rand);

	SG_FREE(strings);
	SG_FREE(data_from_file);
	unlink("ProtobufFileTest_char_output.txt");
}

#endif /* HAVE_PROTOBUF */