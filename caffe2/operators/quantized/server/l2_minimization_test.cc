#include "l2_minimization.h"
#include "caffe2/core/logging.h"

#include <chrono>
#include <fstream>
#include <sstream>

#include <glog/logging.h>
#include <gtest/gtest.h>

using namespace std;
using namespace dnnlowp;

string default_input =
    "-14.4819 12.6175 2048 1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 3 0 0 0 0 0 0 1 1 0 1 0 0 0 1 0 0 1 1 0 0 3 0 0 0 0 0 1 3 0 2 1 2 1 2 1 0 1 0 0 2 3 2 2 4 1 0 1 1 1 2 1 2 1 1 2 1 1 0 2 1 2 3 0 1 1 2 2 2 3 3 5 2 2 2 1 2 3 1 7 9 5 9 9 5 9 9 11 17 11 10 10 9 9 8 9 4 9 4 11 4 8 5 5 9 5 7 12 9 9 3 10 12 3 7 8 13 5 10 12 12 12 9 9 4 14 9 12 10 10 14 6 13 10 10 6 12 12 18 21 16 11 15 10 20 22 22 18 18 17 12 20 17 20 23 16 22 16 20 14 18 24 20 20 31 25 20 25 30 30 33 32 31 29 28 25 36 31 29 26 33 32 37 39 28 36 38 32 48 36 51 55 48 33 39 39 46 47 35 48 68 63 55 56 64 54 56 52 79 68 66 55 87 77 82 81 83 60 59 75 82 66 74 84 86 83 70 89 92 87 93 104 97 90 99 90 94 121 92 98 100 101 109 136 130 129 128 134 134 145 153 149 152 159 152 160 163 162 182 185 172 177 186 213 173 186 195 171 182 190 217 214 224 202 208 257 212 219 264 241 254 258 246 287 285 288 290 297 266 335 304 362 315 343 344 345 345 340 409 394 395 417 437 441 437 403 396 440 437 475 493 486 543 515 507 531 551 578 550 578 599 570 581 634 688 653 650 701 689 710 699 683 771 745 747 788 751 780 913 848 891 909 880 879 947 942 942 944 1068 1020 1060 1037 1110 1109 1096 1140 1167 1171 1208 1261 1251 1231 1312 1274 1316 1302 1370 1369 1458 1485 1501 1541 1522 1590 1588 1629 1799 1745 1728 1809 1839 1949 1864 1935 1920 1984 1969 2119 2140 2094 2208 2238 2277 2210 2472 2393 2618 2623 2594 2632 2647 2690 2695 2868 2906 2952 2968 3068 3213 3275 3236 3305 3345 3398 3472 3442 3593 3632 3833 3931 3827 3914 3985 4105 4139 4339 4446 4494 4565 4545 4782 4970 4990 5780 5311 5393 5375 5519 5654 5707 5734 5982 5942 6219 6318 6499 6462 6769 6698 6925 7072 8299 8541 7730 35660 10820 10040 11238 9865 9868 10676 9940 10353 10709 10335 10782 10696 12063 11168 11320 11734 11776 11929 12211 12437 12482 12902 13339 13332 14756 14075 14250 14308 14904 15099 15509 15868 16217 16618 18011 18694 18755 58761 22265 19945 20945 22434 20167 20671 21440 20621 20762 21792 21253 22358 22186 23578 23755 23604 23619 23934 24192 24927 25115 25666 25917 27543 27167 27018 27794 28804 28854 29380 30138 31421 70215 36359 35925 55743 39643 46541 38148 40062 38126 39360 39752 40569 41204 41932 41709 41835 42753 43952 44445 72601 47776 46669 48032 47467 48002 49251 49725 49964 50692 51811 54123 52562 53493 54314 55730 56716 57162 57971 59029 60032 61012 61913 63985 64570 64535 65761 68345 68703 70116 70787 72436 73202 76169 113303 81878 91403 87685 84575 87267 88611 88085 90390 92325 134000 96940 99299 97637 99505 100296 101272 103266 104403 107430 123506 111776 129581 116497 120189 119407 120348 125704 124118 126740 129191 129733 133399 134878 137058 139250 144731 146812 148338 152072 190935 159985 208894 169915 168230 193660 177385 176865 181398 186568 187614 194906 200232 211866 637370 313955 244761 254378 253000 238019 239661 278798 243444 244863 251450 251875 281095 255861 258096 262660 282346 272143 273498 276499 284072 286397 290493 295217 299562 306633 373466 317403 321624 326122 329935 338138 339275 372918 354175 358879 361193 370070 399737 380676 387712 394729 399316 431035 414993 455984 432027 457498 449814 476975 504634 473154 477803 489399 496667 513851 517560 545632 529784 542026 548026 589932 572150 580596 595161 606018 621153 639424 668268 766270 1237622 782363 749055 735096 791405 791995 757456 768425 776040 786035 799111 833376 853492 841914 883829 884818 883712 896945 936781 928984 945772 1006264 998249 1004424 1021699 1038865 1061104 1116597 1393549 1203808 1226423 1266829 1316189 1584597 1423312 1934099 1470827 1496175 1534637 1519527 1589081 1579775 1597358 1671638 1710996 2315966 1848210 2384805 2027547 2520419 2217233 3193755 2350514 2854147 2328073 2360297 2438732 2762318 2474078 2517502 2562581 2671175 2871633 2764347 2922957 3405789 3055742 3535888 3108723 3161891 3262467 3286487 4773865 3751164 3587091 3601727 3735731 4385026 4463169 4565449 4406105 4636479 4679926 4441157 4437677 4440822 4894005 4903987 4786549 5107863 5047926 5120491 5693089 5517102 5655876 5773186 5689014 5801605 6419603 6300625 6151189 7061284 6648580 6580156 6628528 6865953 7337991 7518336 7674408 7268808 8011681 7569229 7932698 8103726 7988401 8205035 8470319 8603798 8646275 8794354 9389563 9460511 9935716 9470697 9660529 9737260 9778487 10762360 10240827 10241468 10293903 10547641 11404105 11023742 11040799 11210076 11469412 11992906 11723622 11807565 12111508 12116412 12526719 12443274 12687955 12892697 13896509 13839381 14154808 14197607 13838654 14471788 14155982 14409530 15109963 14716948 14970065 15163800 15790522 16216519 15886441 16311904 16545165 16886452 17042598 18089293 17931894 17947333 18647781 18860895 20142964 19516028 19898193 19925027 20420633 20758479 20953720 21325989 22252049 21914669 22240446 22764910 23509713 23425423 24513666 24349767 24771753 25035782 25561492 26000912 26461802 26743417 27707581 28300981 28685197 29038805 29378145 29743136 29857300 30696843 31193241 31535413 32246011 32847112 33244081 33446720 33602678 33968574 35140279 35343116 35872415 36375373 37271884 37658127 38311598 38563508 39491447 40985386 40498747 40782287 41698552 42156338 43214154 43976417 44398181 45754393 45924085 46175036 46928842 47881596 48469275 49180176 49572355 50546517 52338257 52916850 52983303 53572032 54521834 55563262 55861209 57068181 57879978 58669495 60114437 60335227 61286530 61663461 62571720 63928475 65115340 66507855 67390927 68180288 68879548 69762579 71046167 72050429 72718276 73601144 74629636 76125219 77557546 78363864 80757826 82112733 84136551 85672655 87339336 89575803 92356649 94482491 95308835 97883140 100486370 102381626 104126661 107098861 107849598 110046939 111205762 113217139 115189340 117058449 119903792 121774307 124273189 126064068 128738583 132145349 136744605 140522490 143611920 149002600 154565499 166357401 220943249 380624680 242922824 206192970 213454161 224885129 234272651 237541181 229962555 215559602 213317331 210802676 209488838 278801925 295957342 211960550 211725998 213586809 216032281 212313878 214691829 254049470 431135331 299627115 257880768 258986210 241686786 221210463 216762053 216915201 218086136 267606499 328985166 222022886 220837815 219271118 218284596 216236032 216312313 214512874 214319683 214815363 214271325 216605291 219030575 378317595 222436217 222814508 239825320 321825403 296573991 246975669 235773880 219195156 203981045 195269687 189446590 189129430 185708731 286792945 382579729 177169170 175940878 173950470 172193990 172334853 176387589 335528971 334884879 301847527 208722519 170901776 165754706 164699369 169503769 191483907 200965237 170590819 139103476 137641096 135561652 134161896 289568831 131960890 130429746 131722816 133279443 139228240 156769388 217777083 361150135 162408188 154462443 150704951 183342040 254008887 137279919 129515455 123747920 116919252 114084613 112492687 108776361 107712814 107283116 106035509 105123865 104456390 103631484 102884780 102435023 101872171 100278069 99288866 98425803 98089923 97120894 96649751 94559049 93714218 92647136 92166344 90617643 89767174 88889308 88012982 87225160 86946519 85852040 84918178 84337893 83114469 82438175 82128229 81405526 79759502 78999147 78126106 77516179 77403861 76386779 74936287 74231849 73936688 72885367 72659188 70746351 70030849 69858811 70321082 67953055 66996489 66765868 65850606 65372509 64175183 63653388 62902366 62411728 61410694 61000372 60259029 59500529 58850590 58341696 57612633 57521812 56422938 56354581 55828426 54386520 53827030 53341443 52964345 52927384 51424258 50630413 50909146 49357539 48772616 47848548 47347217 47018272 47455083 46503519 45607474 44643259 43820586 43497911 43164717 42410663 42488723 41279647 41097736 40192482 39779736 39502463 39334207 38562766 37711577 37773698 36031881 35222759 34906990 34458680 34391869 33876230 33676579 32479673 31914571 31209766 31139802 30365850 30545698 29592875 29415373 29035457 28143353 28367812 27591382 27229674 27632221 26372275 26121540 25898054 25432778 25555505 24789450 24968412 24107206 23753959 23527800 23269936 23045316 23227518 23147476 22695066 22332302 21710471 21413481 21176955 21500167 20601857 20726367 20236569 20998774 20004844 19097697 19319804 18520245 18393986 18432854 18096955 17691369 17296082 17277546 17188733 16474034 16840513 17305569 15670166 15801373 15271049 15002497 14826521 14621583 15357804 14519846 14002179 13858335 13827443 13383019 13126386 12916933 12922421 12613198 12291672 12117416 12597874 11801263 11657190 11497629 11459238 11383466 11581520 12088935 10766826 11138009 10354715 10306913 10252391 10518305 10443916 9901757 9737638 10442965 9953012 9065882 8885546 8832699 8715375 8626875 9021612 8552820 9035091 8177807 7927433 8242645 7759211 7543230 7536034 7879842 7281256 7229883 7644331 7013732 6931387 6814622 6794666 6402119 6974275 6257497 6741241 6314826 6546644 5813318 6224667 5869511 5498319 5877239 6091985 6350936 5104544 5254585 4988526 5120537 5075334 4345161 4333385 4133609 4017618 4129695 4357278 3943634 3985067 3760426 3628212 3974028 3469888 3386493 3366441 3298151 3866122 3195346 3382820 3588690 3063351 3225668 3348379 3264018 3021319 2642783 2391575 2339719 2263357 2245287 2283341 2221133 2263544 2074394 2076849 2023638 2008142 1923679 2374224 1874712 1788830 1800218 1966099 1772283 1688494 1600276 1614656 1578096 1632424 2182002 1543255 1891504 1511824 1946944 1435361 1324259 1360517 1275724 1358924 1325246 1746468 1234955 1690795 1570740 1080391 1111069 1033566 1040815 1456255 946060 905742 860648 880725 857512 932729 837202 1268859 777105 801632 710771 760334 703919 698575 740968 696917 672576 1063164 622948 655091 596629 675535 1077286 601858 545195 527519 737171 479684 466209 462317 447111 396671 406079 374043 388918 382168 365154 334811 330323 319494 312108 306304 301073 294786 290649 285515 284235 280022 277628 278821 276844 274855 284716 303220 301015 315830 288091 778544 333897 254790 237177 226584 254449 226892 212185 259248 217548 241107 705803 165469 209317 151197 144128 172888 160197 150515 162299 122063 119157 115610 119260 127487 107936 128926 99285 99212 95639 94380 95270 90918 89540 89276 89166 87128 85891 83774 84149 84592 83604 89458 86231 88584 126933 91447 88940 127156 103690 119073 661496 91345 121411 63001 81019 48500 44638 42958 40629 38095 36734 62191 33684 32412 30442 48868 28494 27593 25007 23637 24176 22308 21774 21392 21507 20799 19205 18845 18922 17980 18002 36035 20922 15808 14944 14964 13868 13455 13137 12667 12962 12075 11589 11213 11010 10559 10345 10228 9692 9604 9252 9374 9462 8718 8301 8067 8020 7793 7591 7378 8503 6964 6929 6600 6373 6393 6126 5991 5887 5810 5663 5405 5354 5156 5166 5016 4878 4798 4637 4604 4505 4333 4256 4259 4009 3978 3780 3923 3774 3677 3561 3583 3736 3259 3191 3084 2996 2958 2908 2874 2762 2706 2634 2522 2588 2470 2305 2471 2272 2270 2228 2227 2104 2050 2011 1874 1903 1964 1800 1856 1760 1784 1736 1722 1609 1575 1520 1540 1435 1445 1423 1461 1322 1358 1256 1225 1192 1211 1224 1164 1140 1072 1076 1088 1069 1013 978 929 937 977 930 924 883 807 812 773 804 819 784 763 783 721 1516 681 694 644 587 588 621 597 528 538 533 503 479 481 547 485 454 434 432 419 430 405 401 394 379 376 336 388 334 336 299 364 322 323 260 309 291 313 280 287 266 275 257 225 259 241 259 245 220 212 183 200 211 213 209 168 170 162 170 177 183 149 183 154 180 162 162 175 172 175 179 207 801 115 107 111 93 102 78 88 91 74 79 82 68 85 80 82 72 94 65 73 76 71 62 59 70 56 63 58 55 39 50 36 41 34 56 44 39 47 40 41 37 30 40 36 32 34 40 37 38 34 36 33 31 31 25 31 30 28 26 23 25 25 15 21 14 20 26 27 17 17 26 17 16 14 23 16 16 16 14 14 20 18 22 9 9 8 12 12 15 8 14 11 14 8 11 10 7 11 9 6 9 8 8 5 14 6 4 2 7 4 6 7 5 10 3 5 4 3 4 1 7 3 1 7 1 3 5 1 3 3 2 3 3 6 5 4 2 4 2 1 4 5 1 3 3 4 4 2 3 0 3 1 2 2 1 4 2 0 5 2 4 2 0 1 1 0 4 1 1 2 3 0 2 1 2 1 1 1 2 0 1 1 0 0 0 0 3 2 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1";

namespace {
  class ChooseQuantizationTest : public testing::TestWithParam<bool> {};
};

INSTANTIATE_TEST_CASE_P(
    InstantiationName,
    ChooseQuantizationTest,
    testing::Bool());

TEST_P(ChooseQuantizationTest, L2MinimizationTest) {
  bool preserve_sparsity = GetParam();
  int precision = 8;

  float min, max;
  int nbins;
  istringstream ist(default_input);
  ist >> min >> max >> nbins;

  vector<uint64_t> bins;
  for (int i = 0; i < nbins; ++i) {
    uint64_t cnt;
    ist >> cnt;
    bins.push_back(cnt);
  }
  assert(bins.size() == nbins);

  Histogram hist = Histogram(min, max, bins);

  chrono::time_point<chrono::system_clock> begin, end;
  begin = chrono::system_clock::now();
  TensorQuantizationParams qparam =
      L2ErrorMinimization().ChooseQuantizationParams(
          hist, preserve_sparsity, precision);
  end = chrono::system_clock::now();
  double dt = chrono::duration<double>(end - begin).count();

  LOG(INFO) << "L2 error minimizing quantization takes " << dt << " sec.";
  if (preserve_sparsity) {
    EXPECT_FLOAT_EQ(qparam.scale, 0.055523049);
    EXPECT_EQ(qparam.zero_point, 128);
    EXPECT_FLOAT_EQ(qparam.Min(), -7.10695);
    EXPECT_FLOAT_EQ(qparam.Max(), 7.0514274);
  } else {
    EXPECT_FLOAT_EQ(qparam.scale, 0.053343643);
    EXPECT_EQ(qparam.zero_point, 136);
    EXPECT_FLOAT_EQ(qparam.Min(), -7.2547355);
    EXPECT_FLOAT_EQ(qparam.Max(), 6.3478932);
  }

  LOG(INFO) << qparam.scale << " " << qparam.zero_point << " " << qparam.Min()
            << " " << qparam.Max() << " " << dt;
}
