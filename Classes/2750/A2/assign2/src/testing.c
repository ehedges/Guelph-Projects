#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VCardParser.h"
#include "utilities.h"
#include "LinkedListAPI.h"

int main(int argc, char const *argv[])
{

	VCardErrorCode error;

	Parameter* tempParam;

	Card* obj;
	DateTime* dt;
	char* first;
	char* second;
	char* third;
	char* JSONstring;
	char* errorString;
	//int extenValue;

	first = malloc(sizeof(char)*100);
	second = malloc(sizeof(char)*100);
	third = malloc(sizeof(char)*100);


	first = strcpy(first,"!test!");
	second = strcpy(second,"|TESTED|");

	printf("Write Card tests\n");
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	deleteProperty(obj->fn);
	obj->fn = NULL;
	error = writeCard("files/error.vcf",obj);
	errorString = printError(error);
	printf("Obj with no FN %s\n",errorString);
	deleteCard(obj);
	free(obj);
	free(errorString);	

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	free(obj->fn->name);
	obj->fn->name = NULL;
	error = writeCard("files/error.vcf",obj);
	errorString = printError(error);
	printf("Obj with no FN %s\n",errorString);
	deleteCard(obj);
	free(obj);
	free(errorString);	

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	clearList(obj->fn->values);
	free(obj->fn->values);
	obj->fn->values = NULL;
	error = writeCard("files/error.vcf",obj);
	errorString = printError(error);
	printf("Obj with no FN %s\n",errorString);
	deleteCard(obj);
	free(obj);
	free(errorString);


/*
	printf("%s\n",first);

	extenValue = -1;

	extenValue = extensionCheck("file.ged","ged",4);
	printf("Test1: Valid: %d expected: 0\n,",extenValue);
	extenValue = extensionCheck("","ged",4);
	printf("Test2: No inpit file: %d expected: 4\n",extenValue);
	extenValue = extensionCheck(NULL,"ged",4);
	printf("Test3: NUll input file: %d expected:1\n",extenValue);
	extenValue = extensionCheck("file.ged","gef",4);
	printf("Test4: Invalid extension: %d expected: \n",extenValue);
	extenValue = extensionCheck("fileged","ged",4);
	printf("Test5: No dot for extension: %d expected: \n",extenValue);
	extenValue = extensionCheck("file.ged","",4);
	printf("Test6: No extension given: %d expected: \n",extenValue);
	extenValue = extensionCheck("file.ged","ged",2);
	printf("Test7: Extension longer than type length: %d expected: 3\n",extenValue);
	extenValue = extensionCheck("file.gedas","gedas",6);
	printf("Test8: Extension longer than type length: %d expected: \n",extenValue);

	strcpy(third,"ABCD");
	extenValue = lineEndingChecker(third,"D");
	printf("Test1: Vaild: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(NULL,"C");
	printf("Test2: NULL input: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,NULL);
	printf("Test3: NULL ending %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,"\r");
	printf("Test4: Wrong ending: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,"ABCD");
	printf("Test5: Multiple characters: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,"ABCDABCD");
	printf("Test6: Double characters: %d expected: 0\n",extenValue);
*/
	//(*obj) = malloc(sizeof(Card));
	char* stuff;
	error = OK;
	//printf("Error:%d\n",error);
/*
	error = createCard("testCard.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCard2.vcf",obj);
	deleteCard(obj);
	free(obj);
	error = createCard("files/testCard2.vcf",(&obj));
	error  = validateCard(obj);
	deleteCard(obj);
	free(obj);
	error = createCard("files/testCard2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard testCard:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);


	error = createCard("testCard-Ann.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardAnn2.vcf",obj);
	deleteCard(obj);
	free(obj);

	error = createCard("files/testCardAnn2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard testCardAnn:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-AnnUTC.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardAnnUTC2.vcf",obj);	
	deleteCard(obj);
	free(obj);

	error = createCard("files/testCardAnnUTC2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard testCardAnnUTC:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-BdayText.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardBdayText2.vcf",obj);
	deleteCard(obj);
	free(obj);

	error = createCard("files/testCardBdayText2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard testCardBdayText:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-BdayTime.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardBdayTime2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardBdayTime2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard testCarBdayTime:%s\n",stuff);	
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-bothDT.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardBOTHDT2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardBOTHDT2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard BOTHDT:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);/*
	error = createCard("testCardGroup.vcf",(&obj));
	error  = validateCard(obj);
	stuff = printError(error);
	printf("Error from validateCard Group:%s\n",stuff);
	deleteCard(obj);*//*
	error = createCard("testCardMin.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testMin2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testMin2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard MIN:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-MoreFold.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardMoreFold2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardMoreFold2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard MoreFold:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardN-compVal.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardNCompVal2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardNCompVal2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard compVal:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProp-Param.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardProp-Param2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardProp-Param2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard ParamsVals:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProp-ParamsVals.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardPropParamsVals2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardPropParamsVals2.vcf",(&obj));	
	stuff = printError(error);
	printf("Error from validateCard ParamsVals:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProps-compVal.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardProp-compVal2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardProp-compVal2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard compVals:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProps-Groups.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardProps-Groups.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardProps-Groups.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard Groups:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProps-Params.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardProps-Params.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardProps-Params.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard Params:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProps-ParamsVals.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardProps-ParamsVals2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardProps-ParamsVals2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard ParamsVals:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCardProp-simpleVal.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardSimpleVal2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardSimpleVal2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard simpleVal:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-SimpleFold1.vcf",(&obj));
	error  = validateCard(obj);	
	error = writeCard("files/testCardSimpleFold1.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardSimpleFold1.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard fold:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-SimpleFold2.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardSimpleFold2.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardSimpleFold2.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard fold2:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	free(obj);

	error = createCard("testCard-TruncBday.vcf",(&obj));
	error  = validateCard(obj);
	error = writeCard("files/testCardTruncBday.vcf",obj);
		deleteCard(obj);
	free(obj);

	error = createCard("files/testCardTruncBday.vcf",(&obj));
	stuff = printError(error);
	printf("Error from validateCard truncBday:%s\n",stuff);
	free(stuff);
	deleteCard(obj);
	stuff = printError(error);
	printf("%s\n",stuff);
	free(stuff);
	char* string = printCard(obj);
	free(string);
	deleteCard(obj);
	deleteCard(NULL);
	string = printCard(NULL);
	free(string);
	free(obj);
	free(third);
	free(first);
	free(second);

	obj = JSONtoCard(NULL);
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	Property* tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	JSONstring = propToJSON(tempProp);
	printf("%s\n",JSONstring);
	free(JSONstring);
	char* nulltesting = strListToJSON(NULL);

	if(strcmp(nulltesting,"[\"\"]")==0)
	{

		printf("ISOOGD\n");

	}
	free(nulltesting);

	deleteProperty(tempProp);

	tempProp = JSONtoProp(NULL);
	if(tempProp == NULL)
	{

		printf("NULLRETURN\n");
		
	}
	tempProp = JSONtoProp(NULL);
	JSONstring = propToJSON(NULL);
	if(strlen(JSONstring) > 0)
	{

		printf("NULLS\n");

	}
	free(JSONstring);

	addProperty(obj,tempProp);
	tempProp = JSONtoProp(NULL);
	if(tempProp == NULL)
	{

		printf("HERERERERER\n");

	}

	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"TEL\",\"values\":[\"+1-418-656-9254\",\"ext=102\"]}");
	addProperty(obj,tempProp);
	addProperty(NULL,tempProp);
*/
	dt = JSONtoDT("{\"isText\":true,\"date\":\"\",\"time\":\"\",\"text\":\"circa 1960\",\"isUTC\":false}");
	JSONstring = dtToJSON(dt);
	printf("%s\n{\"isText\":true,\"date\":\"\",\"time\":\"\",\"text\":\"circa 1960\",\"isUTC\":false}\n",JSONstring);
	deleteDate(dt);
	obj->anniversary = JSONtoDT(JSONstring);
	if(obj->anniversary == NULL)
	{
		printf("ANNI\n");

	}
	free(JSONstring);
	dt = JSONtoDT("{\"isText\":false,\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":true}");
	JSONstring = dtToJSON(dt);
	printf("{\"isText\":false,\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":true}\n");
	printf("%s\n",JSONstring);
	deleteDate(dt);
	obj->birthday = JSONtoDT(JSONstring);
	if(obj->birthday == NULL)
	{
		printf("BIRTH\n");

	}/*
	free(JSONstring);
	addProperty(obj,NULL);
	JSONstring = dtToJSON(NULL);
	printf("%s\n",JSONstring);
	free(JSONstring);
	//dt = JSONtoDT();	
	error  = validateCard(obj);
	stuff = printError(error);
	printf("Error from validateCard JSON:%s\n",stuff);
	char* stuffzts = printCard(obj);
	printf("JSON:%s\n",stuffzts);
	free(stuffzts);
	free(stuff);
	deleteCard(obj);
	free(obj);
	char* validateError;
	printf("Validate Card tests\n");
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	deleteProperty(obj->fn);
	obj->fn = NULL;
	validateError = printError(validateCard(obj));
	printf("Obj with no FN %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	dt = JSONtoDT("{\"isText\":false,\"date\":\"\",\"time\":\"\",\"text\":\"\",\"isUTC\":true}");
	obj->birthday = dt;
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with Datetime having no date or time%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"TEL\",\"values\":[\"+1-418-656-9254\",\"ext=102\",\"ext=102\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with TEL having 3 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"TEL\",\"values\":[\"+1-418-656-9254\",\"ext=102\"]}");
	free(tempProp->parameters);
	tempProp->parameters = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with TEL having NULL parameters %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"TEL\",\"values\":[\"+1-418-656-9254\",\"ext=102\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with tel having 2values:%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"TEL\",\"values\":[\"+1-418-656-9254\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with tel having 1 value:%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"TEL\",\"values\":[\"\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with tel having no values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"GENDER\",\"values\":[\"M\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but with Gender having 1 values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"GENDER\",\"values\":[\"M\"]}");
	free(tempProp->parameters);
	tempProp->parameters = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but with Gender having 1 values and null parameters%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"GENDER\",\"values\":[\"M\",\"M\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but with Gender having 2 values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"GENDER\",\"values\":[\"M\",\"M\"]}");
	addProperty(obj,tempProp);
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"gender\",\"values\":[\"M\",\"M\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but with 2 Genders having 2 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"GENDER\",\"values\":[\"M\",\"M\",\"M\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but with Gender having 3 values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);
	
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"ADR\",\"values\":[\"\",\"Suite D2-630\",\"2875 Laurier\",\"Quebe\",\"QC\",\"G1V 2M2\",\"Canada\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with ADR 7 values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"ADR\",\"values\":[\"\",\"Suite D2-630\",\"2875 Laurier\",\"Quebe\",\"QC\",\"G1V 2M2\",\"Canada\"]}");
	free(tempProp->parameters);
	tempProp->parameters = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with ADR 7 values and Null Parameters%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"ADR\",\"values\":[\"\",\"Suite D2-630\",\"2875 Laurier\",\"Quebe\",\"QC\",\"Canada\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with ADR 6 values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"ORG\",\"values\":[\"\",\"\",\"Suite D2-630\",\"2875 Laurier\",\"Quebe\",\"QC\",\"G1V 2M2\",\"Canada\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with ORG with 8 values%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"\",\"name\":\"asdfasdfasdf\",\"values\":[\"\",\"\",\"Suite D2-630\",\"2875 Laurier\",\"Quebe\",\"QC\",\"G1V 2M2\",\"Canada\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with Nonexistant property %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N with 5 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);
	

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"ing. jr,M.Sc.\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N with 4 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);
	

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N with 6 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);



	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":false,\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":true}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);
/*
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":\"false\",\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":\"true\"}");
	dt->text = NULL;
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt with Null text, and false isText%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":\"false\",\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":\"true\"}");
	dt->date = NULL;
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt->date is NULL%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":\"false\",\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":\"true\"}");
	dt->time = NULL;
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt->time is NULL%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);
*//*
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":false,\"date\":\"\",\"time\":\"\",\"text\":\"\",\"isUTC\":true}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt isText is false and there is empty strings for date and text%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":false,\"date\":\"1234\",\"time\":\"4321\",\"text\":\"asdf\",\"isUTC\":true}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt isText is false and there is stuff in text%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":true,\"date\":\"19540203\",\"time\":\"\",\"text\":\"Date\",\"isUTC\":true}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt->isText is true and there is date->date has values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":true,\"date\":\"\",\"time\":\"19540203\",\"text\":\"Date\",\"isUTC\":true}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt->isText is true and there is date->date has values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":true,\"date\":\"\",\"time\":\"\",\"text\":\"Date\",\"isUTC\":true}");
	dt->UTC = true;
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt->isText is true and isUTC is true%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":true,\"date\":\"\",\"time\":\"\",\"text\":\"\",\"isUTC\":true}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt->isText is true and the text is empty.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	dt = JSONtoDT("{\"isText\":false,\"date\":\"19540203\",\"time\":\"123012\",\"text\":\"\",\"isUTC\":false}");
	obj->birthday = dt;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but dt and isUTC false%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	//tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	//addProperty(obj,tempProp);
	free(obj->optionalProperties);
	obj->optionalProperties = NULL;
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but Null optional Properties %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);
	
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	free(obj->fn->name);
	obj->fn->name = NULL;
	validateError = printError(validateCard(obj));
	printf("Obj with FN name NULLF %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	free(obj->fn->group);
	obj->fn->group = NULL;
	validateError = printError(validateCard(obj));
	printf("Obj with gfroup NULLF %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	free(tempProp->name);
	tempProp->name = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with Null property name with 5 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	free(tempProp->group);
	tempProp->group = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with Null group with 5 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	strcpy(tempProp->name,"");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with empty name with 5 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	free(tempProp->parameters);
	tempProp->parameters = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	//printf("%d\n",getLength(tempProp->parameters));
	printf("Obj with FN  but error with Null parameters %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	tempParam = malloc(sizeof(Parameter)+sizeof(char)*1000);
	strcpy(tempParam->name,"Name");
	strcpy(tempParam->value,"TESTING");
	insertBack(tempProp->parameters,(void*)tempParam);
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N  with 5 values and manual param input.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

		obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	tempParam = malloc(sizeof(Parameter)+sizeof(char)*1000);
	strcpy(tempParam->name,"");
	strcpy(tempParam->value,"TESTING");
	insertBack(tempProp->parameters,(void*)tempParam);
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N  with 5 values and manual param empty name input.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	insertBack(tempProp->parameters,NULL);
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N  with 5 values and manual null parameters.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	tempParam = malloc(sizeof(Parameter)+sizeof(char)*1000);
	strcpy(tempParam->name,"Name");
	strcpy(tempParam->value,"");
	insertBack(tempProp->parameters,(void*)tempParam);
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N  with 5 values and param empty value input.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"FN\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"FN\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with mutliple FN values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"lang\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"lAnG\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with single valiue mutliple prop,.. Language, both hav e different lower/upper values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);


	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"Kind\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"lAnG\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with 1 mutliple Language and Kind single prop, both hav e different lower/upper values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);


	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"kind\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"KIND\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);
	/*tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"KIND\",\"values\":[\"Perreault Simon\"]}");
	addProperty(obj,tempProp);*//*
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with 2 King, both hav e different lower/upper values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"Kind\",\"values\":[\"Perreault Simon\",\"\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with empty name with Kind (SingleValue, single prop), both having 2 values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"KIND\",\"values\":[\"Perreault Simon\",\"\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with empty name with 1 SingleValue multi prop with multiple values, both hav e different lower/upper values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"TZ\",\"values\":[\"Perreault Simon\",\"\"]}");
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with empty name with 1 SingleValue multi prop with multiple values, both hav e different lower/upper values %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"TZ\",\"values\":[\"Perreault Simon\"]}");
	free(tempProp->group);
	tempProp->group = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with 1 SingleValue multi prop, Have Null group %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);


	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"Kind\",\"values\":[\"Perreault Simon\"]}");
	free(tempProp->group);
	tempProp->group = NULL;
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with Kind (SingleValue, single prop) %s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);





/*
	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	tempParam = malloc(sizeof(Parameter)+sizeof(char)*1000);
	tempParam->name = NULL;
	strcpy(tempParam->value,"TESTING");
	insertBack(tempProp->parameters,(void*)tempParam);
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N  with 5 values and manual param input.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);


	obj = JSONtoCard("{\"FN\":\"Simon Perreault\"} ");
	tempProp = JSONtoProp("{\"group\":\"testing\",\"name\":\"N\",\"values\":[\"Perreault\",\"Simon\",\"\",\"\",\"ing. jr,M.Sc.\"]}");
	tempParam = malloc(sizeof(Parameter)+sizeof(char)*1000);
	strcpy(tempParam->name,"Name");
	tempParam->value = NULL;
	insertBack(tempProp->parameters,(void*)tempParam);
	addProperty(obj,tempProp);
	validateError = printError(validateCard(obj));
	printf("Obj with FN  but error with N  with 5 values and manual param input.%s\n",validateError);
	deleteCard(obj);
	free(obj);
	free(validateError);

*/
	/*
	error = createCard(NULL,(&obj));
	printf("Null Error:%d\n",error);

	error = createCard("",(&obj));
	printf("Empty Error:%d\n",error);

	error = createCard("Nocard.vcf",(&obj));
	printf("No existant Card Error:%d\n",error);

	error = createCard("utilities.c",(&obj));
	printf("Exist file wrong extension Error:%d\n",error);

	error = createCard("",(&obj));
	printf("Wrong extensions Error:%d\n",error);

	error = createCard("",(&obj));
	printf("Empty Error:%d\n",error);
*/
/*
	for (error = OK ; error < 6; error++)
	{
		string = printError(error);
		printf("%s\n",string);
		free(string);
	}
*/
	return 0;
}