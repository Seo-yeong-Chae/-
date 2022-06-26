select ui.gender, 
ui.age_band, 
sum(unitsold) as unitsold, 
sum(gmv) as gmv,
count(distinct oo.userid) as customer_count, 
round(cast(sum(unitsold) as numeric)/count(distinct oo.userid),4) as unitsold_per_customer,
sum(gmv)/count(distinct oo.userid) as gmv_per_customer
from online_order oo 
join item i on oo.itemid = i.category_id 
join user_info ui on oo.userid = ui.userid 
group by 1,2
order by 3 desc
;
