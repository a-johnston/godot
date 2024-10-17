/**************************************************************************/
/*  fuzzy_search.h                                                        */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef FUZZY_SEARCH_H
#define FUZZY_SEARCH_H

#include "core/object/ref_counted.h"
#include "core/variant/array.h"
#include "core/variant/variant.h"

class Tree;

class FuzzyTokenMatch : public RefCounted {
	GDCLASS(FuzzyTokenMatch, RefCounted);

protected:
	static void _bind_methods() {}

public:
	int score{};
	int token_length;
	int matched_length{};
	Vector2i interval = Vector2i(-1, -1);  // x and y are both inclusive indices
	Vector<Vector2i> substrings;  // x is start index, y is length

	void add_substring(const int substring_start, const int substring_length);
	bool intersects(const Vector2i other_interval);

	_FORCE_INLINE_ int misses() const { return token_length - matched_length; }
};

class FuzzySearchResult : public RefCounted {
	GDCLASS(FuzzySearchResult, RefCounted);

protected:
	static void _bind_methods() {}

public:
	String target;
	int score{};
	int bonus_index = -1;
	int miss_budget{};
	Vector2i match_interval = Vector2i(-1, -1);
	Vector<Ref<FuzzyTokenMatch>> token_matches;

	bool can_add_token_match(Ref<FuzzyTokenMatch> &p_match);
	void score_token_match(Ref<FuzzyTokenMatch> &p_match);
	void add_token_match(Ref<FuzzyTokenMatch> &p_match);
};

class FuzzySearch : public RefCounted {
	GDCLASS(FuzzySearch, RefCounted);

public:
	static Vector<Ref<FuzzySearchResult>> search_all(const String &p_query, const PackedStringArray &p_search_data);
	static void draw_matches(Tree *p_tree);
};

#endif // FUZZY_SEARCH_H
