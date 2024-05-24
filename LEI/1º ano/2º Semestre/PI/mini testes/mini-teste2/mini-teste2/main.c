#include <stdio.h>
int maiorSeq (int v[], int N){
  int i, j, count, max=0;
  for (i = 0; i < N; i++){
        count = 1;
        for (j = i + 1; j < N; j++) {
            if (v[j] < v[j-1]) {
                count++;
            } else {
                break;
            }
        }

        if (count > max) {
            max = count;
        }
        if (max==7){
            printf ("%d\n",v[i]);
            break;
        }
    }
  printf("Maior seq %d\n", max);
  return max;
}

int main(){

    int sequencia[1024] = {8091, 8760, 532, 5493, 6565, 6087, 138, 4428, 2586, 6898, 4409, 339, 9137, 310, 8535, 8116, 2226, 4750, 1628, 3444, 5076, 5909, 5724, 2059, 5262, 8127, 9643, 7203, 9282, 8096, 6246, 542, 6251, 2353, 8187, 6803, 5239, 1566, 1972, 3294, 6199, 6386, 6181, 8954, 1158, 448, 2537, 2364, 9724, 9552, 3025, 6258, 7810, 5673, 831, 7761, 416, 21, 4742, 7929, 8199, 6449, 4541, 3717, 2144, 1680, 1368, 4659, 8896, 4598, 5848, 9095, 4212, 2675, 3583, 8994, 3142, 5044, 6143, 1276, 2799, 7592, 9022, 8299, 3143, 1854, 6112, 8013, 9108, 7603, 4567, 8788, 9749, 6388, 8955, 826, 473, 928, 7789, 3676, 3410, 4007, 1292, 2495, 1178, 5540, 9582, 3688, 314, 6993, 3633, 6090, 199, 648, 3365, 3039, 7625, 8237, 8174, 2491, 6208, 9073, 8586, 4916, 3821, 5692, 4793, 949, 6078, 2866, 9598, 2181, 8145, 5293, 3363, 4740, 3664, 8706, 7309, 44, 423, 1804, 59, 4077, 2857, 2222, 9672, 3465, 5966, 6338, 6330, 7618, 7584, 6430, 8722, 8564, 1358, 3823, 9981, 2460, 8176, 2549, 5128, 9931, 319, 5988, 5070, 6537, 1679, 1149, 7903, 482, 2797, 9803, 1460, 311, 1463, 1449, 3623, 4574, 3839, 2792, 6226, 1342, 3349, 1643, 9347, 2507, 6587, 7539, 7026, 4702, 3226, 6055, 4207, 8328, 4293, 4411, 7165, 202, 7155, 2417, 4617, 7428, 127, 8728, 5439, 696, 6923, 7336, 5835, 6265, 7878, 9792, 7420, 6358, 392, 2353, 7725, 2411, 3433, 3728, 8632, 732, 4891, 1447, 5917, 172, 8024, 6499, 9454, 7967, 9227, 3606, 8932, 1396, 2121, 4372, 5257, 1433, 5498, 2140, 112, 655, 3236, 784, 1118, 2323, 771, 267, 1966, 6778, 4494, 4166, 3972, 6466, 6197, 6257, 5946, 5195, 8452, 5544, 4872, 2240, 8942, 154, 9550, 3213, 8944, 7377, 1631, 4658, 3511, 4901, 4385, 4641, 1020, 1074, 2610, 5954, 5309, 8615, 4484, 771, 1331, 6267, 3600, 8818, 1401, 711, 9564, 4822, 6035, 5274, 7397, 4349, 8047, 103, 5527, 4720, 3863, 8485, 6066, 5764, 834, 7917, 4197, 8432, 4794, 8670, 663, 5641, 7046, 6858, 7170, 4668, 2909, 6449, 6519, 7296, 1547, 5488, 6637, 9908, 9680, 429, 6120, 3849, 3191, 640, 5448, 8700, 9972, 5605, 146, 2521, 4636, 1455, 1291, 108, 8407, 1032, 4844, 5302, 897, 1225, 3685, 3093, 4871, 9320, 2638, 5647, 3547, 2273, 7319, 4085, 4995, 7755, 5053, 6489, 561, 4055, 3484, 6406, 9029, 9536, 2834, 9422, 2890, 3789, 200, 3492, 9405, 8255, 6289, 9118, 9937, 9772, 4382, 1122, 2447, 2657, 2637, 6016, 5887, 3660, 6484, 6811, 291, 5445, 5852, 4848, 3837, 7940, 541, 8237, 8084, 1725, 5246, 9411, 3795, 6365, 1407, 3908, 5271, 5054, 1798, 9914, 6830, 2433, 6849, 2132, 1925, 3545, 9593, 4724, 4594, 9959, 2593, 4152, 8541, 7682, 5735, 927, 5553, 6048, 1160, 9403, 8844, 3825, 5923, 3481, 1662, 3789, 5462, 3484, 727, 6266, 3513, 7807, 5737, 8812, 7480, 9795, 6433, 8028, 8775, 5566, 2152, 1218, 7266, 6777, 6017, 5506, 2641, 4304, 7090, 4307, 238, 7100, 4523, 8252, 6369, 5619, 7190, 2308, 4911, 6397, 6349, 1989, 9091, 6956, 1524, 3762, 6479, 9438, 6514, 5557, 8107, 6775, 2507, 6611, 7148, 7552, 3825, 911, 438, 7480, 5060, 5907, 5774, 5307, 7938, 4959, 4561, 5035, 9129, 5656, 4647, 9500, 6779, 4997, 2151, 4143, 3301, 5844, 6273, 1898, 2321, 758, 8702, 5629, 1358, 7823, 3250, 7847, 3453, 7471, 4911, 2354, 936, 8923, 1977, 2339, 9175, 3520, 101, 1333, 4788, 4526, 410, 7038, 1091, 1400, 690, 4248, 9959, 2007, 7628, 7485, 359, 8537, 7523, 3951, 3608, 9079, 402, 5457, 5818, 5147, 3136, 7075, 4990, 9759, 563, 3829, 8458, 6800, 4350, 6393, 8272, 5047, 8004, 6888, 3540, 2127, 5614, 7880, 2350, 5440, 3444, 7870, 2909, 2362, 4762, 8782, 9164, 5866, 5006, 9011, 4390, 5192, 5158, 399, 1137, 9, 8600, 758, 6158, 3582, 5473, 4144, 7028, 8680, 157, 5269, 3981, 9850, 5212, 7021, 9052, 9330, 4125, 3794, 781, 2718, 6303, 4590, 7634, 1521, 6948, 4208, 2548, 8546, 1813, 3783, 8552, 5306, 1565, 2822, 3403, 9758, 3789, 4864, 6749, 5176, 2070, 8748, 9994, 7072, 9814, 316, 969, 205, 7610, 9119, 854, 5275, 6431, 9085, 1775, 7430, 6945, 1792, 5058, 7730, 1549, 8841, 5504, 6119, 8727, 5540, 7923, 1337, 5022, 8713, 1921, 8912, 9918, 647, 8836, 7474, 3206, 6269, 1222, 8579, 2221, 8740, 4687, 8977, 1794, 7390, 7444, 5163, 1024, 304, 8507, 7471, 502, 2362, 2590, 413, 1427, 9992, 3529, 8069, 4821, 8744, 8668, 3617, 4611, 2089, 6007, 1006, 2047, 4844, 8530, 120, 1189, 910, 5791, 4151, 4652, 6397, 4409, 9452, 3817, 8872, 3843, 2020, 8761, 1043, 9700, 1671, 8853, 4147, 6789, 66, 471, 8974, 6215, 5517, 610, 1243, 1367, 544, 7998, 8850, 3378, 2029, 5576, 412, 2793, 5669, 9202, 2447, 8485, 6788, 842, 3057, 1690, 6065, 6730, 2756, 2014, 8834, 158, 6903, 7595, 2925, 9635, 7316, 5349, 8532, 6429, 3115, 3890, 155, 8530, 4374, 263, 3783, 4472, 7133, 5483, 4272, 7420, 2738, 3937, 609, 1939, 1318, 1840, 1849, 1535, 3831, 5293, 1204, 6327, 5423, 8053, 3781, 1069, 6518, 7079, 4981, 2397, 3441, 6992, 9679, 5166, 4613, 349, 6636, 1431, 8565, 6230, 2553, 4574, 9680, 7389, 5348, 9207, 4703, 1449, 8256, 1603, 7845, 3018, 4576, 9435, 7756, 6214, 2151, 5585, 799, 7639, 5795, 1697, 4632, 5250, 9591, 1506, 9881, 9428, 9067, 2170, 3996, 7557, 7091, 7533, 5593, 4193, 4190, 1572, 6028, 9739, 2994, 95, 1193, 1486, 1282, 3189, 1917, 2243, 4519, 3795, 261, 7274, 5628, 6522, 4595, 9795, 1860, 7516, 5930, 666, 3103, 6788, 9446, 1276, 6483, 48, 1670, 6753, 9326, 3875, 8609, 7165, 8853, 2091, 4155, 7175, 4954, 8896, 3069, 7523, 2412, 3728, 9815, 9491, 2019, 6162, 7969, 5283, 5158, 853, 7123, 2399, 3037, 2430, 9248, 5442, 3356, 8576, 5190, 1927, 6314, 6350, 8106, 4022, 3744, 1421, 4213, 419, 6496, 1277, 1473, 7604, 6921, 7392, 7265, 3354, 2324, 2214, 1739, 6815, 2073, 3371, 4948, 2052, 9027, 7139, 1636, 8342, 4442, 8633, 2921, 4202, 8558, 5172, 5951, 1076, 4957, 1324, 6398, 6909, 6670, 3632, 2194, 698, 1185, 1499, 6430, 8845, 5087, 5272, 9432, 7689, 3352, 9125, 7751, 9940, 2627, 9858, 2650, 5664, 6167, 68, 8369, 1018, 5988, 7702, 9607, 9844, 7412, 3847, 2609, 5251, 2015, 2879, 218, 6799, 8625, 3574, 3895, 6539, 962, 9296, 9574, 3479, 133, 7490, 5051, 816, 4082, 9146, 1301, 6804, 5778, 2435, 6358, 2635, 9052, 2328, 901, 6689, 7219, 5393, 1835, 6790, 272, 267, 3660, 2137, 8039, 1432, 9349, 8812, 9893, 7048, 6113, 4464, 9841, 5979, 9912, 1541, 8864, 7318, 2084, 449, 3540, 4002, 4230};
    printf("maoir: %d\n", maiorSeq(sequencia,1024));


    return 0;

    }
