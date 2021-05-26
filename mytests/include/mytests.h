#ifndef MYTESTS_H
#define MYTESTS_H

#define ASSERT_EQUALS(a,b)		if ((a)!=(b)) printf("\nLine %d: ASSERT_EQUALS failed\n", __LINE__);
#define ASSERT_NOT_EQUALS(a,b)		if ((a)==(b)) printf("\nLine %d: ASSERT_NOT_EQUALS failed\n", __LINE__);

// «а false принимаетс€ 0, за true - любое значение, отличное от нул€
#define ASSERT_TRUE(expression)		if (!(expression)) printf("\nLine %d: ASSERT_TRUE failed\n", __LINE__);
#define ASSERT_FALSE(expression)	if ((expression)) printf("\nLine %d: ASSERT_FALSE failed\n", __LINE__);

#define ASSERT_NULL(pointer)		if ((pointer)!=NULL) printf("\nLine %d: ASSERT_NULL failed\n", __LINE__);
#define ASSERT_NOT_NULL(pointer)	if ((pointer)==NULL) printf("\nLine %d: ASSERT_NOT_NULL failed\n", __LINE__);

#endif