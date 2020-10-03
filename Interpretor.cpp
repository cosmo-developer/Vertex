#include "Interpretor.h"
#include "InstanceManager.h"
#include <string.h>
Interpretor::Interpretor(std::vector<Token*> stream) {
	this->streams = stream;
	this->ct = this->streams[this->position];
}
void Interpretor::interpret() {
	while (this->position < streams.size()) {
		if (ct->t() == TT::INPUT_VAR) {
			next();
			while (ct->t() != TT::SEMI_COLON) {
				Token* t=eat(TT::IDENTIFIER);
				input_vars[t->val()] = 1.0;
				if (ct->t() == TT::COMMA) { eat(TT::COMMA); }
				else {
					eat(TT::SEMI_COLON);
					break;
				}
			}
			if (ct->t() == TT::NUMBER) {
				for (std::map<std::string, double>::iterator it = input_vars.begin(); it != input_vars.end(); ++it) {
					Token* t = eat(TT::NUMBER);
					input_vars[it->first] = atof(t->val().c_str());
				}
			}

		}
		else if (ct->t() == TT::VERTEX) {
			next();
			while (ct->t() != TT::SEMI_COLON) {
				Token* t = eat(TT::IDENTIFIER);
				eat(TT::EQUAL);
				Token* tx = eat(TT::OPTYPE);
				vertices[t->val()] =VertexObject();
				vertices[t->val()].active = false;
				vertices[t->val()].contain = 0.0;
				vertices[t->val()].op = tx->val();
				vertices[t->val()].name = t->val();
				if (ct->t() == TT::COMMA) { eat(TT::COMMA); }
				else {
					eat(TT::SEMI_COLON);
					break;
				}
			}
		}
		else if (ct->t() == TT::WRITE) {
			next();
			eat(TT::LPAREN);
			while (ct->t() != TT::RPAREN) {
				Token* temp = eat(TT::IDENTIFIER);
				if (input_vars.find(temp->val()) != input_vars.end()) {
					std::cout << temp->val() << ":" << input_vars[temp->val()] << std::endl;
				}
				else if (vertices.find(temp->val()) != vertices.end()) {
					std::cout << temp->val() << ":" << vertices[temp->val()].contain << std::endl;
				}
				else {
					previous();
					InstanceManager::handler->undefinedIdentifier(ct);
				}
				if (ct->t() == TT::COMMA) { eat(TT::COMMA); }
				else { eat(TT::RPAREN);eat(TT::SEMI_COLON); break; }

			}
		}
		else if (ct->t() == TT::IDENTIFIER) {
			std::vector<std::string> sequence;
			Token* id = eat(TT::IDENTIFIER);
			sequence.push_back(id->val());
			while (ct->t() != TT::SEMI_COLON) {
				eat(TT::DASH);
				eat(TT::RIGHT_ANGULAR_BRACKET);
				id=eat(TT::IDENTIFIER);
				sequence.push_back(id->val());
			}
			eat(TT::SEMI_COLON);
			for (int i = 0;i < sequence.size()-1;i++) {
				if (vertices.find(sequence[i]) != vertices.end() && i<sequence.size()-1) {
					VertexObject vo = operate(vertices[sequence[i + 1]], vertices[sequence[i]].contain);
					vertices[sequence[i + 1]].contain = vo.contain;
					vertices[sequence[i + 1]].active = vo.active;
					vertices[sequence[i + 1]].name = vo.name;
				}
				else if (input_vars.find(sequence[i]) != input_vars.end() && i < sequence.size() - 1) {
					VertexObject vo = operate(vertices[sequence[i + 1]], input_vars[sequence[i]]);
					vertices[sequence[i + 1]].contain = vo.contain;
					vertices[sequence[i + 1]].active = vo.active;
					vertices[sequence[i + 1]].name = vo.name;
				}
			}
		}
		else {
			next();
		}
	}
}
VertexObject Interpretor::operate(VertexObject out, double in) {
	if (out.active) {
		if (strcmp(out.op.c_str(),"DIVIDE")==0) {
			out.contain = out.contain / in;
		}
		else if (strcmp(out.op.c_str(),"MINUS")==0) {
			out.contain = out.contain - in;
		}
		else if (strcmp(out.op.c_str(), "TIMES") == 0) {
			out.contain = out.contain * in;
		}
		else if (strcmp(out.op.c_str(), "PLUS") == 0) {
			out.contain = out.contain + in;
		}
	}
	else {
		out.contain = in;
		out.active = true;
	}
	return out;
}
//asking for next token
void Interpretor::next() {
	this->position++;
	if (this->position < streams.size()) {
		this->ct = this->streams[this->position];
	}
	/*else {
		InstanceManager::handler->eofException(ct);//If token ended and request come then throw an Eof exception at value lien col
	}*/
}
void Interpretor::previous() {
	if (this->position == 0) {
		this->next();
	}
	else {
		this->position--;
		this->ct = this->streams[this->position];
	}
}
std::string Interpretor::getByType(TT type) {
	switch (type) {
	case TT::INPUT_VAR:
		return "input_var";
	case TT::IDENTIFIER:
		return "identifier";
	case TT::NUMBER:
		return "DoubleValue";
	case TT::VERTEX:
		return "vertex";
	case TT::PLUS:
		return "PLUS";
	case TT::MINUS:
		return "MINUS";
	case TT::DIVIDE:
		return "DIVIDE";
	case TT::TIMES:
		return "TIMES";
	case TT::EQUAL:
		return "=";
	case TT::COMMA:
		return ",";
	case TT::SEMI_COLON:
		return ";";
	case TT::DASH:
		return "-";
	case TT::RIGHT_ANGULAR_BRACKET:
		return ">";
	case TT::WRITE:
		return "write";
	case TT::RPAREN:
		return ")";
	case TT::LPAREN:
		return "(";
	case TT::OPTYPE:
		return "Vertex Operand type";
	default:
		return "";
	}

}
Token* Interpretor::eat(TT type) {
	Token* toReturn = NULL;
	char* err = new char[100];
	if (ct->t() == type) {
		toReturn = ct;
	   this->next();
	}
	else {
#ifdef _MSC_VER
		sprintf_s(err,100, "Expected:'%s' but found:'%s' at line:%d on col:%d\n",
			this->getByType(type).c_str(),
			this->ct->val().c_str(),
			this->ct->l(),
			this->ct->c()
		);
#else
		sprintf(err, "Expected:'%s' but found:'%s' at line:%d on col:%d\n",
			this->getByType(type).c_str(),
			this->ct->val().c_str(),
			this->ct->l(),
			this->ct->c()
		);
#endif
		InstanceManager::handler->throwHazardas(err);
	}
	return toReturn;
}