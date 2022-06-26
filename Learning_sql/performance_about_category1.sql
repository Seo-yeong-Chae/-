select c.cate1 ,
cast(round(sum(cast(discount as numeric))/sum(gmv),2)*100 as varchar) || '%' as discount_rate, 
sum(cast(gmv as numeric) - discount) as paid_amount,
cast(round(sum(cast(product_profit as numeric))/sum(gmv),2)*100 as varchar) || '%' as product_margin,
cast(round(sum(cast(total_profit as numeric))/sum(gmv),2)*100 as varchar) || '%' as total_margin
from online_order oo 
join item i on oo.itemid = i.category_id 
join category c on i.category_id = c.id
group by 1
order by 3 desc
;
