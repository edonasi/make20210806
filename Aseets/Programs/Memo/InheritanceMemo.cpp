/*
継承についてのメモ

・ClImg
   | - ClMovie
   | - ClImgDiv
   | - ClImgColl
   
・ClImgオーバーライド関数一覧
   | - VOID SetIsDraw();
   |	| -			 /					/ ClImgColl
   |
   | - VOID SetIsDraw(BOOL is_draw);	
   |	| - ClMovie / ClImgDiv			/ ClImgColl
   |
   | - BOOL Load(string path, string cpp_name, string ins_name);
   |	| -			/ ClImgDiv			/ ClImgColl
   |
   | - BOOL Load(string path, int abs_speed, string cpp_name, string ins_name);
   |	| -			/ ClImgDiv:private	/ 
   |
   | - BOOL Load(string path, int abs_speed, BOOL is_draw, string cpp_name, string ins_name);
   |	| -			/ ClImgDiv:private	/ 
   |
   | - BOOL Load(string path, string cpp_name, string ins_name, BOOL is_draw);
   |	| -			/ ClImgDiv:private	/ 
   |
   | -  VOID Draw();
   |	| -			/ ClImgDiv
   |
   | - VOID Delete();
   |	| -			/ ClImgDiv			/ ClImgColl
   |
   | - VOID Move();
   |	| -			/					/ ClImgColl
   |
   | - BOOL MmLoad(string path, string cpp_name, string ins_name);
   |	| - ClMovie / ClImgDiv:private	/ 
   |
   | -
   |	| -

   
・ClColl
   | - ClCollPoint
   | - ClCollRect

・ClCollオーバーライド関数一覧
	なし
   
   */