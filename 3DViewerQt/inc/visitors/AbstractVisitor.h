#pragma once

class Model;
class PlainCamera;

class AbstractVisitor
{
public:
    virtual ~AbstractVisitor() = 0;

    virtual void visit(Model &model) = 0;
    virtual void visit(PlainCamera &camera) = 0;
};