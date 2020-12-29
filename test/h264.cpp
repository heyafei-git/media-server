#include "test.h"
#include "h264/h264.h"
#include "h264/H264LayerSelector.h"
#include "h264/h264depacketizer.h"

class H264Plan: public TestPlan
{
public:
	H264Plan() : TestPlan("H264 test plan")
	{
		
	}
	
	virtual void Execute()
	{
		testDepacketizer();
		
		testSelector();
	}
	
	void testDepacketizer()
	{
		BYTE data[1033] = {
			0x7c, 0x45, 0x9f, 0xc1, 0x10, 0xe8, 0xe4, 0x7c,
			0xff, 0x55, 0x07, 0x48, 0x88, 0xf7, 0x1d, 0x44,
			0x26, 0x01, 0xd1, 0xf7, 0x6a, 0x0f, 0x74, 0x6a,
			0x5c, 0x26, 0xe4, 0xd3, 0x26, 0x99, 0x31, 0x0f,
			0x1e, 0xa0, 0xce, 0xcb, 0xd3, 0x4f, 0xff, 0x89,
			0xc1, 0x7f, 0x7e, 0xb7, 0xdc, 0x6e, 0x95, 0x95,
			0x77, 0x49, 0xfe, 0x11, 0x89, 0x92, 0xce, 0xa0,
			0xf5, 0xdf, 0xa8, 0x11, 0x48, 0xed, 0x16, 0x9f,
			0x10, 0x39, 0xb8, 0xd1, 0xb8, 0x23, 0x0b, 0x27,
			0x8f, 0xc1, 0x7a, 0x42, 0x24, 0x80, 0xba, 0x71,
			0x5c, 0x76, 0xf6, 0xdb, 0xff, 0x1e, 0xa0, 0xa3,
			0xff, 0xfa, 0x49, 0x7d, 0x31, 0xe3, 0xd8, 0x0c,
			0x62, 0xa6, 0x47, 0x4f, 0x83, 0xd4, 0x02, 0x06,
			0x76, 0x8a, 0xb7, 0xf6, 0xbe, 0xbf, 0x4b, 0x70,
			0x72, 0xff, 0xc2, 0x13, 0xe1, 0x44, 0xf2, 0xaf,
			0xc8, 0xcf, 0xdf, 0xaa, 0xae, 0xfd, 0xf5, 0x7c,
			0x99, 0x5d, 0x6a, 0x3a, 0xae, 0x75, 0xfd, 0xdd,
			0x99, 0xd8, 0xb5, 0xeb, 0xc5, 0x65, 0xa4, 0x7f,
			0xf5, 0xf2, 0x09, 0x87, 0xf2, 0xc0, 0xe6, 0x7c,
			0xb6, 0x52, 0xbc, 0x51, 0x45, 0xd2, 0x9f, 0x33,
			0x16, 0x7b, 0x97, 0x3f, 0xff, 0xf4, 0x12, 0xed,
			0x6a, 0x9a, 0xcb, 0x08, 0x30, 0x1b, 0x33, 0x67,
			0xfb, 0xff, 0xe8, 0x55, 0x43, 0x43, 0x2f, 0x92,
			0xfb, 0x2b, 0x55, 0xad, 0x0d, 0xa7, 0xae, 0x6f,
			0x9f, 0xe0, 0x7c, 0x4c, 0x89, 0xe1, 0x7e, 0x7c,
			0x1f, 0xa1, 0xab, 0xa9, 0x7a, 0xed, 0x61, 0xf5,
			0x09, 0xc1, 0x4f, 0x72, 0xd6, 0x9b, 0x58, 0xf0,
			0x60, 0xd4, 0x5e, 0x19, 0x93, 0xbb, 0x7b, 0x7d,
			0xfa, 0xfc, 0x70, 0x05, 0x5b, 0x0a, 0xd4, 0x90,
			0xa5, 0xb8, 0xee, 0x43, 0x9c, 0x0e, 0xa6, 0xd7,
			0xff, 0x2e, 0xcb, 0x7b, 0x4d, 0x8f, 0x57, 0xff,
			0xe5, 0xdc, 0xba, 0x0d, 0xf2, 0xe0, 0xa2, 0xfb,
			0xe0, 0x20, 0x0f, 0x7b, 0xc4, 0x6b, 0xe9, 0x47,
			0x4e, 0xe9, 0x1a, 0xe3, 0xe5, 0xe5, 0x3d, 0x43,
			0x96, 0x36, 0x8c, 0xe6, 0xda, 0x9b, 0x0c, 0x49,
			0xed, 0x19, 0x6b, 0xde, 0xa0, 0x62, 0xf4, 0x60,
			0xb1, 0x55, 0xa3, 0x2c, 0x7d, 0x23, 0x45, 0x89,
			0xf1, 0xcd, 0xa1, 0xc2, 0xc4, 0x73, 0x80, 0x1c,
			0x6f, 0xaf, 0x3f, 0x2f, 0x7f, 0x77, 0xec, 0x83,
			0x88, 0x16, 0xbf, 0x3b, 0xbd, 0xe1, 0x12, 0x40,
			0x13, 0x35, 0x5b, 0x5b, 0xef, 0xff, 0xf8, 0xac,
			0x04, 0xdf, 0x71, 0xf3, 0xca, 0xaf, 0xc7, 0xcf,
			0xe8, 0x13, 0x6f, 0xef, 0xff, 0x91, 0x07, 0xcd,
			0x78, 0x51, 0x04, 0x23, 0x64, 0x56, 0x57, 0x1b,
			0x9f, 0xb8, 0xd0, 0xb7, 0xf7, 0xf4, 0x48, 0xfd,
			0xd4, 0x1c, 0x1d, 0xcf, 0xcc, 0x2e, 0x9d, 0x7c,
			0x73, 0xaa, 0xbe, 0xaa, 0xa2, 0xf0, 0x2a, 0x8f,
			0x12, 0xf4, 0x9f, 0x5b, 0x54, 0xc2, 0x65, 0x33,
			0x94, 0x58, 0xb2, 0x99, 0xed, 0xfa, 0xd2, 0x88,
			0xbf, 0x57, 0x5c, 0x19, 0x43, 0xc4, 0x8e, 0x1e,
			0x6a, 0x99, 0x81, 0x8c, 0x54, 0xa6, 0xe5, 0x17,
			0xb8, 0x71, 0xee, 0xac, 0x79, 0xae, 0x12, 0xbc,
			0xa0, 0x4e, 0x9b, 0x60, 0x6c, 0xf9, 0xb3, 0xd5,
			0x21, 0x54, 0x82, 0xcc, 0x15, 0xde, 0x64, 0x1a,
			0xee, 0x85, 0x68, 0x58, 0xf2, 0x49, 0x5d, 0xf3,
			0x47, 0x70, 0xdf, 0xa6, 0x90, 0x79, 0x3b, 0x7c,
			0x7a, 0x5b, 0x7f, 0xf7, 0xc3, 0x59, 0x2a, 0x88,
			0x10, 0x82, 0x7c, 0x26, 0x33, 0x70, 0xc4, 0x5c,
			0xd1, 0x91, 0x1e, 0x62, 0x58, 0x98, 0xdf, 0x6f,
			0xb7, 0xae, 0x63, 0x8b, 0xbb, 0x90, 0x5d, 0x67,
			0x45, 0xf2, 0xd8, 0x44, 0xb3, 0xd2, 0xb7, 0x7f,
			0x9f, 0x20, 0xfe, 0x21, 0x9f, 0x1b, 0x03, 0x9b,
			0xd2, 0x3a, 0x6f, 0xd9, 0xdf, 0xde, 0x4a, 0x24,
			0x64, 0x04, 0x7c, 0xd5, 0x78, 0x26, 0x5d, 0xf8,
			0x08, 0x46, 0x69, 0x0d, 0x1b, 0x52, 0xed, 0xc6,
			0x65, 0xf9, 0xf0, 0xf7, 0xc6, 0x63, 0x24, 0xc1,
			0xb6, 0xe0, 0x09, 0xaa, 0x19, 0x58, 0x2b, 0x1f,
			0xf0, 0xa5, 0xd4, 0x7e, 0xa3, 0xad, 0x7f, 0x74,
			0x58, 0x12, 0x9a, 0x08, 0x60, 0x26, 0xfa, 0x38,
			0xf7, 0xff, 0x45, 0xd9, 0x73, 0xb1, 0xda, 0xfe,
			0x9e, 0x4d, 0x34, 0xe9, 0xa7, 0x1a, 0x49, 0x08,
			0x92, 0x00, 0x61, 0x65, 0xed, 0x0d, 0x5b, 0xca,
			0xaa, 0xdb, 0xc4, 0x06, 0xf8, 0x2a, 0x25, 0x72,
			0x43, 0x5a, 0xe5, 0x87, 0xf9, 0xd6, 0xef, 0x6f,
			0xa3, 0xe5, 0xe9, 0xdd, 0x3e, 0xd4, 0x29, 0xf7,
			0xc2, 0xaf, 0xe3, 0xc8, 0x27, 0x6f, 0x26, 0xe4,
			0x6b, 0xca, 0x4d, 0xdf, 0xdc, 0x22, 0x4e, 0x9b,
			0xcf, 0xff, 0xf2, 0x93, 0x1c, 0xe0, 0x0f, 0x56,
			0x93, 0x4d, 0x7f, 0x36, 0xfc, 0x6b, 0x59, 0xd8,
			0x7f, 0xca, 0x19, 0x71, 0x9b, 0xd7, 0x9d, 0x9c,
			0x0a, 0x60, 0xd2, 0x06, 0x75, 0xf0, 0x86, 0x80,
			0x12, 0xc8, 0x99, 0x21, 0xff, 0xff, 0xff, 0x2c,
			0x9f, 0xa1, 0x76, 0xb5, 0x50, 0x03, 0x47, 0x95,
			0xf1, 0xb5, 0x25, 0x01, 0x94, 0xda, 0x90, 0x19,
			0xa8, 0x7d, 0x06, 0xab, 0x50, 0x4a, 0xfc, 0x48,
			0x0a, 0x7b, 0x9b, 0xff, 0x55, 0x3c, 0xf7, 0xaa,
			0xa4, 0xb5, 0x88, 0x51, 0x45, 0x7e, 0x6d, 0x71,
			0x3e, 0x69, 0x3c, 0x07, 0xcf, 0xef, 0xc0, 0x3f,
			0xf0, 0x94, 0xd9, 0xab, 0x35, 0xaa, 0x3a, 0x9c,
			0xf5, 0x5f, 0xf9, 0x3a, 0xf2, 0xac, 0xcb, 0xc8,
			0xfd, 0xfb, 0xc5, 0xda, 0x7b, 0x9f, 0x3f, 0xff,
			0xe5, 0x43, 0x29, 0x77, 0x19, 0xf3, 0x5d, 0xa5,
			0x8f, 0x50, 0x39, 0x57, 0x93, 0x8f, 0x8c, 0xbb,
			0xfd, 0xa6, 0x9b, 0x6c, 0x26, 0xa0, 0x22, 0xa3,
			0xc4, 0x07, 0xda, 0xb1, 0x71, 0x16, 0xbf, 0xdb,
			0xda, 0xed, 0xcf, 0x33, 0x03, 0x12, 0xb9, 0x2e,
			0x41, 0x95, 0xb7, 0xe2, 0xf5, 0x5f, 0x39, 0x8f,
			0x53, 0xea, 0xb1, 0x5c, 0x57, 0x7d, 0x33, 0xbb,
			0x5a, 0xad, 0x6a, 0xbf, 0xd7, 0x13, 0x8f, 0x11,
			0x1f, 0x15, 0x63, 0xd5, 0x96, 0xcb, 0x9d, 0xfd,
			0x71, 0x5f, 0x0e, 0xc1, 0x3a, 0x2e, 0x4e, 0x1c,
			0xbb, 0xe1, 0x0c, 0x05, 0xe8, 0xe0, 0xed, 0x3f,
			0xff, 0xda, 0xd8, 0xf5, 0x12, 0xb5, 0xbf, 0x3f,
			0xfa, 0xdf, 0x85, 0xd6, 0xff, 0xf1, 0xeb, 0x1f,
			0xd8, 0x1b, 0xbc, 0xab, 0x31, 0xb8, 0xda, 0xdf,
			0xde, 0x4b, 0xfd, 0x82, 0xad, 0x89, 0x5b, 0xff,
			0xf2, 0x7a, 0xf4, 0xf2, 0x69, 0x94, 0x95, 0x4e,
			0x2d, 0xf8, 0x78, 0x7f, 0x6f, 0x6d, 0x33, 0x31,
			0xd3, 0xb1, 0x77, 0xc9, 0x8a, 0xda, 0xda, 0xab,
			0x5b, 0x58, 0xe7, 0x3a, 0x8f, 0xb2, 0x56, 0x5e,
			0xac, 0x95, 0x97, 0xf9, 0x7f, 0xb1, 0x3b, 0xf6,
			0xc7, 0x17, 0x6f, 0xa7, 0x7c, 0xc0, 0x15, 0x57,
			0xfe, 0xc5, 0x60, 0x31, 0x9f, 0xec, 0x4a, 0xef,
			0x00, 0xe9, 0x1a, 0x4c, 0x2a, 0xaf, 0x80, 0x82,
			0x04, 0xc6, 0x7a, 0x84, 0x15, 0x03, 0x10, 0x73,
			0x6a, 0xbb, 0xf8, 0x83, 0xef, 0xa4, 0xef, 0xff,
			0xe2, 0xeb, 0x95, 0x5c, 0x7d, 0xdb, 0xf7, 0xd3,
			0xa4, 0xd5, 0xb0, 0x89, 0x20, 0x26, 0x69, 0xd1,
			0xee, 0x5f, 0xeb, 0xaf, 0xf2, 0x2e, 0x40, 0x1f,
			0xc8, 0x13, 0xd4, 0xdb, 0x66, 0x67, 0xc2, 0xa4,
			0x82, 0x33, 0x24, 0xff, 0x3f, 0x81, 0x1e, 0xfc,
			0xf7, 0xc8, 0x53, 0xb9, 0x0e, 0xa7, 0x73, 0xbd,
			0xc7, 0xa8, 0x7f, 0x42, 0xb7, 0xba, 0x00, 0x05,
			0x16, 0x86, 0x8c, 0x39, 0x6b, 0x8e, 0xf8, 0x2a,
			0xd3, 0xad, 0xfd, 0x4f, 0xff, 0xdb, 0xd7, 0xa5,
			0x7a, 0x1f, 0x55, 0xff, 0x7b, 0xff, 0xc5, 0x6b,
			0x5e, 0x04, 0x28, 0x3a, 0x35, 0xa1, 0x7d, 0xbf,
			0xd4, 0x73, 0xff, 0xde, 0x7b, 0x84, 0x9d, 0x7e,
			0x7f, 0xb4, 0x5a, 0x0b, 0xd4, 0x7a, 0x2e, 0xdf,
			0x80
		};
		
		H264Depacketizer depacketizer;
		
		depacketizer.AddPayload(data,sizeof(data));
			
	}
	
	void testSelector()
	{
		BYTE data[1074] = {56,1,225,33,224,74,2,80,
			115,132,191,193,7,36,254,54,
			227,41,20,69,194,33,43,22,
			219,79,213,124,243,238,66,105,
			71,218,63,8,79,137,194,32,
			248,183,8,152,232,6,47,3,
			193,89,43,40,83,104,254,223,
			92,102,221,3,219,85,178,202,
			26,39,238,6,225,57,248,140,
			231,196,41,6,228,176,39,150,
			85,181,197,53,255,191,218,78,
			121,149,10,125,100,172,14,78,
			169,232,135,42,205,165,93,200,
			222,224,18,3,230,128,0,152,
			19,252,245,92,201,17,79,163,
			29,246,130,20,69,227,23,82,
			158,237,150,49,206,18,140,182,
			159,240,55,145,199,31,119,4,
			22,237,167,130,132,162,168,37,
			242,4,249,109,211,12,63,234,
			13,174,121,103,236,70,146,219,
			255,197,214,146,177,168,170,87,
			1,67,44,93,185,228,78,75,
			61,63,169,5,80,139,18,23,
			248,11,249,111,77,119,110,107,
			46,170,229,126,12,201,66,53,
			65,248,115,46,62,16,192,193,
			4,12,75,80,192,89,206,50,
			86,1,77,165,207,158,92,127,
			195,10,103,114,25,200,5,105,
			112,15,228,99,240,26,76,80,
			125,251,133,25,98,128,191,65,
			127,230,253,133,16,67,95,96,
			156,16,169,66,109,177,52,140,
			83,203,206,53,186,46,201,149,
			152,147,130,56,110,195,196,149,
			148,192,248,98,149,22,82,172,
			18,64,242,239,105,34,16,106,
			88,40,109,20,30,240,109,0,
			54,216,123,45,37,86,81,13,
			12,150,36,99,148,83,131,98,
			80,194,217,144,132,96,18,214,
			214,134,196,99,230,102,83,86,
			221,83,165,72,36,53,226,202,
			255,55,245,205,239,116,240,51,
			38,79,156,16,5,250,109,52,
			140,195,108,194,215,245,195,193,
			58,180,186,135,59,1,149,164,
			69,239,31,251,125,46,89,80,
			33,86,11,155,63,140,187,206,
			99,32,111,158,71,136,90,211,
			117,255,63,196,16,108,13,25,
			6,144,23,34,69,204,193,98,
			137,228,223,10,148,2,164,68,
			67,176,98,134,120,42,250,166,
			58,228,77,244,246,235,4,166,
			85,250,142,45,188,102,127,113,
			188,75,149,127,190,45,213,121,
			10,249,39,20,252,89,45,62,
			19,114,160,103,117,251,0,166,
			6,178,25,152,2,76,33,0,
			120,56,18,128,148,28,225,47,
			243,224,52,240,232,30,106,1,
			142,24,20,68,0,2,108,133,
			250,217,180,92,250,132,207,36,
			192,71,136,105,73,57,38,138,
			219,245,172,93,55,191,17,100,
			172,198,174,94,202,232,44,25,
			102,215,222,255,230,21,144,15,
			24,93,244,23,242,11,26,95,
			61,92,30,191,68,166,54,149,
			114,255,137,184,61,103,103,134,
			160,196,254,31,150,68,50,0,
			9,75,31,211,36,198,209,227,
			168,22,42,175,2,24,102,218,
			252,120,119,9,216,64,233,220,
			133,148,106,60,153,118,207,53,
			152,89,130,126,143,136,135,72,
			42,175,126,151,223,96,21,42,
			180,82,134,227,17,217,72,200,
			171,57,227,84,237,151,2,21,
			86,237,196,23,66,125,234,237,
			248,238,66,44,232,16,96,55,
			109,108,92,135,159,174,32,212,
			32,28,42,247,99,123,139,148,
			214,81,195,230,182,11,127,157,
			179,246,196,92,45,166,27,87,
			200,29,243,251,140,138,219,237,
			69,61,94,63,233,220,131,158,
			129,91,252,75,108,23,56,253,
			190,187,169,38,240,134,146,121,
			137,209,10,245,162,194,186,52,
			28,82,207,49,75,48,41,63,
			108,32,54,15,105,141,52,53,
			130,167,52,36,214,182,65,191,
			179,183,171,220,137,101,239,142,
			96,156,240,10,224,81,253,128,
			240,18,69,130,253,192,97,11,
			81,103,137,211,38,124,75,192,
			64,1,75,62,143,122,34,141,
			215,116,116,120,143,104,79,46,
			215,210,139,6,157,152,175,206,
			82,123,251,61,85,96,92,191,
			59,61,233,108,146,41,28,19,
			186,208,228,13,96,6,216,20,
			2,130,131,147,189,27,158,46,
			190,149,170,250,13,217,192,73,
			26,222,188,205,227,23,243,137,
			212,232,160,72,97,146,162,81,
			43,72,114,192,108,214,175,67,
			223,95,159,238,116,48,169,38,
			56,91,232,36,56,141,243,49,
			58,51,156,228,27,138,128,138,
			64,232,170,5,124,13,224,43,
			163,36,133,183,234,16,188,234,
			193,132,121,81,230,84,119,234,
			221,71,159,249,143,60,174,185,
			152,17,32,110,72,181,54,204,
			248,74,103,19,64,215,125,185,
			224,208,69,214,28,245,211,90,
			95,2,113,188,145,139,113,188,
			142,133,64,137,214,72,75,52,
			72,81,140,229,162,171,95,185,
			145,74,230,79,26,51,248,175,
			132,59,40,9,109,135,147,108,
			37,211,122,68,137,209,147,200,
			148,102,63,153,67,44,91,131,
			222,180,40,231,235,109,17,186,
			254,238,109,100,140,151,157,24,
			94,246,159,177,49,102,247,44,
			91,177,14,140,140,227,186,233,
			207,250,40,2,45,183,66,61,
			149,187,8,249,69,83,250,254,
			72,199,51,181,237,163,77,57,
			89,128};
		
		H264LayerSelector selector;
		RTPPacket::shared rtp = std::make_shared<RTPPacket>(MediaFrame::Video,VideoCodec::H264);
		rtp->SetPayload((BYTE*)data,sizeof(data));
		
		bool mark = false;
		selector.Select(rtp,mark);
		
		selector.GetSeqParameterSet().Dump();
		selector.GetPictureParameterSet().Dump();
	}
};

	
H264Plan h264;

