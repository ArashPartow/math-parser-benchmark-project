#include "cpuid.h"
#include <string>
#include <deque>
#include <algorithm>

#include "libcpuid/libcpuid.h"

void dump_cpuid(FILE* file)
{
   if (0 == file)
      return;

   struct cpu_raw_data_t raw;
   struct cpu_id_t data;

   cpuid_set_warn_function(NULL);

   cpuid_set_verbosiness_level(0);

   if (cpuid_get_raw_data(&raw) < 0)
   {
      fprintf(file, "Cannot obtain raw CPU data!\n");
      fprintf(file, "Error: %s\n", cpuid_error());
      return;
   }

   if (cpu_identify(&raw, &data) < 0)
   {
      fprintf(file, "Error identifying the CPU: %s\n", cpuid_error());
      return;
   }

   fprintf(file, "  - CPU Name      : %s\n",          data.brand_str);
   fprintf(file, "  - Num. cores    : %d\n",          data.num_cores);
   fprintf(file, "  - Num. logical  : %d\n",   data.num_logical_cpus);
   fprintf(file, "  - Total logical : %d\n", data.total_logical_cpus);
   fprintf(file, "  - L1 D cache    : %d KB\n",   data.l1_data_cache);
   fprintf(file, "  - L1 I cache    : %d KB\n", data.l1_instruction_cache);
   fprintf(file, "  - L2 cache      : %d KB\n",        data.l2_cache);
   if (-1 != data.l3_cache)
   fprintf(file, "  - L3 cache      : %d KB\n",        data.l3_cache);
   fprintf(file, "  - L1D assoc.    : %d-way\n",       data.l1_assoc);
   fprintf(file, "  - L2 assoc.     : %d-way\n",       data.l2_assoc);
   if (-1 != data.l3_assoc)
   fprintf(file, "  - L3 assoc.     : %d-way\n",       data.l3_assoc);
   fprintf(file, "  - L1D line size : %d bytes\n", data.l1_cacheline);
   fprintf(file, "  - L2 line size  : %d bytes\n", data.l2_cacheline);
   if (-1 != data.l3_cacheline)
   fprintf(file, "  - L3 line size  : %d bytes\n", data.l3_cacheline);
   fprintf(file, "  - CPU clock     : %d MHz\n",         cpu_clock());
   fprintf(file, "  - Features      : ");

   std::deque<std::string> feature_list;

   for (int i = 0; i < NUM_CPU_FEATURES; ++i)
   {
      if (data.flags[i])
      {
         feature_list.push_back(cpu_feature_str((cpu_feature_t)i));
      }
   }

   std::sort(feature_list.begin(),feature_list.end());

   std::string feat_str;

   for (std::size_t i = 0; i < feature_list.size(); ++i)
   {
      feat_str += feature_list[i] + " ";
      if (feat_str.size() >= 54)
      {
         fprintf(file, "%s\n",feat_str.c_str());
         fprintf(file, "                    ");
         feat_str = "";
      }
   }

   if (!feat_str.empty())
   fprintf(file, "%s\n\n",feat_str.c_str());
   fflush(file);
}

