#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <libxml/parser.h>  
  
static int  
parseDoc(char* docname) {  
    xmlDocPtr doc;  
    xmlNodePtr cur;  
    xmlNodePtr cur2;  
    xmlKeepBlanksDefault(0);  
  
    doc = xmlParseFile(docname);  
  
    if(doc == NULL) {  
        fprintf(stderr, "doc error!\n");  
        return 0;  
    }  
  
    cur = xmlDocGetRootElement(doc);  
  
    if(cur == NULL) {  
        fprintf(stderr, "root error!\n");  
        xmlFreeDoc(doc);  
        return 0;  
    }  
  
    //if(xmlStrcmp(cur->name, (const xmlChar*)"root")) {  
    //    printf("end\n");  
    //    return 0;  
    //}  
  
    cur = cur->children;  
    while(cur != NULL) {  
	printf("name:%s\n", cur->name);
	cur2 = cur->children;
	while (cur2 != NULL) {
        	printf("name=%s content=%s\n",cur2->name,   
        	        (char*)xmlNodeGetContent(cur2));  
        	        //cur->content);  
        	cur2 = cur2->next;  
	}
	cur = cur->next;
    }
    xmlFreeDoc(doc);  
    return 0;  
}  
  
int main() {  
    char* docname = "package.xml";  
    parseDoc(docname);  
    return 1;  
}  
