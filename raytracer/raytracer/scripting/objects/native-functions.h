#pragma once

#include "scripting/objects/function.h"
#include "math/vector3d.h"
#include "math/point3d.h"

namespace scripting
{
    namespace library
    {
        class Addition : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        class Subtraction : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        class Multiplication : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        class Equality : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        class Comparison : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;

            virtual bool compare(double, double) const = 0;
        };

        class LessThan : public Comparison
        {
        protected:
            bool compare(double, double) const override;
        };

        class GreaterThan : public Comparison
        {
        protected:
            bool compare(double, double) const override;
        };

        class NotLessThan : public Comparison
        {
        protected:
            bool compare(double, double) const override;
        };

        class NotGreaterThan : public Comparison
        {
        protected:
            bool compare(double, double) const override;
        };

        class Negation : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        //class CreatePoint : public Function
        //{
        //protected:
        //    std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        //};

        //class CreateVector : public Function
        //{
        //protected:
        //    std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        //};

        class GetXYZ : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;

            virtual double get(const math::Point3D&) const = 0;
            virtual double get(const math::Vector3D&) const = 0;
        };

        class GetX : public GetXYZ
        {
        protected:
            double get(const math::Point3D&) const override;
            double get(const math::Vector3D&) const override;
        };

        class GetY : public GetXYZ
        {
        protected:
            double get(const math::Point3D&) const override;
            double get(const math::Vector3D&) const override;
        };

        class GetZ : public GetXYZ
        {
        protected:
            double get(const math::Point3D&) const override;
            double get(const math::Vector3D&) const override;
        };

        class Allocate : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        class ReadHeap : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };

        class WriteHeap : public Function
        {
        protected:
            std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
        };
    }
}