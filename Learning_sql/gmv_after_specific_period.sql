select *
from gmv_trend gt 
where (gt.yyyy || gt.mm) >
(to_char(now() - interval '2 year', 'yyyymm') || to_char(now() - interval '2 year', 'yyyymm')) 
;

